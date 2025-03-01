#include "ltbpch.h"
#include "Scripts/Context.h"

namespace LTB {
    void ScriptContext::InitVariable(){
        // runtime type identifiers
        mLua["TRANSFORM"] = TypeID<TransformComponent>();

        // add transform data type
        mLua.new_usertype<Transform>("Transform",
            "Translation", &Transform::translation,
            "Rotation", &Transform::rotation,
            "Scale", &Transform::scale
        );

        // add vector2 data type
        mLua.new_usertype<Vector2>("Vector2",
            // sol::constructors<Vector2(), Vector2(float, float)>(),
            "x", &Vector2::x,
            "y", &Vector2::y
        );

        // add vector3 data type
        mLua.new_usertype<Vector3>("Vector3",
            // sol::constructors<Vector3(), Vector3(float, float, float)>(),
            "x", &Vector3::x,
            "y", &Vector3::y,
            "z", &Vector3::z
        );

        // add vector4 data type
        mLua.new_usertype<Vector4>("Vector4",
            // sol::constructors<Vector3(), Vector3(float, float, float)>(),
            "x", &Vector4::x,
            "y", &Vector4::y,
            "z", &Vector4::z,
            "w", &Vector4::w
        );

        // add Camera3D data type
        mLua.new_usertype<Camera3D>("Camera3D",
            "Position", &Camera3D::position,
            "Target", &Camera3D::target,
            "Up", &Camera3D::up,
            "FOVY", &Camera3D::fovy,
            "Projection", &Camera3D::projection
        );

        // add Camera2D data type
        mLua.new_usertype<Camera2D>("Camera2D",
            "Target", &Camera2D::target,
            "Offset", &Camera2D::offset,
            "Rotation", &Camera2D::rotation,
            "Zoom", &Camera2D::zoom
        );

        // add color data type
        mLua.new_usertype<Color>("Color",
            "r", &Color::r,
            "g", &Color::g,
            "b", &Color::b,
            "a", &Color::a
        );

        // add rectangle data type
        mLua.new_usertype<Rectangle>("Rectangle",
            "x", &Rectangle::x,
            "y", &Rectangle::y,
            "width", &Rectangle::width,
            "height", &Rectangle::height
        );
    }

    ScriptContext::ScriptContext(EntityRegistry* scene){

        // import lua libraries
        mLua.open_libraries(sol::lib::base);

        // load LTB api module
        mLua.require_file("Inputs", "Data/Script/Engine/Input.lua");
        mLua.require_file("Core", "Data/Script/Engine/Core.lua");

        InitVariable();

        //register callback
        SetApiFunctions(scene);
    }

    // create instance of existing script
    bool ScriptContext::AttachScript(Entity& entity, const std::string& name){
        // check if handle is correct and has a constructor
        if(!mLua[name].valid() && !mLua[name]["Constructor"].valid()){
            LTB_ERROR("failed to create script: invalid script name!");
            return false;
        }

        // create instance script
        auto object = mLua[name]["Constructor"](entity.ID());
        LTB_INFO("Entity name: ", entity.GetName());

        // check if obj is valid
        if(!object.valid()){
            // handle failure
            sol::error error = object;
            sol::call_status status = object.status();
            LTB_ERROR("failed to create script: {}", error.what());

            return false;
        }

        auto& instance = entity.Get<ScriptComponent>().Instance;
        instance = CreateScope<Script>(object, name);
        instance->OnStart();
        return true;
    }

    std::string ScriptContext::LoadScript(const std::string& filepath){
        std::filesystem::path path(filepath);
        auto scriptName = path.stem().string();

        // check if already loaded
        if(mLua[scriptName].valid()){
            return scriptName;
        }

        // check if modules are loaded
        if(!mLua["Initializer"].valid()) 
        {
            LTB_ERROR("failed to load script! core not initialized!");
            return "";
        }

        // check if script file exits
        if(!std::filesystem::exists(path))
        {
            LTB_ERROR("failed to load script: invalid file path!");
            return "";
        }

        // create script class handle
        mLua[scriptName] = mLua["Initializer"]();
        mLua.script_file(filepath);   
        return scriptName;
    }

    // registers functions to interact with entity
    void ScriptContext::SetApiFunctions(EntityRegistry* scene)
    {
        // api function to get entity transform
        mLua.set_function("ApiGetTransform", [this, scene] (EntityID entity)
        {
            // LTB_INFO("TRAnsform");
            return std::ref(scene->get<TransformComponent>(entity).Transforms);
        });

        //temp
        mLua.set_function("ApiGetPositionX", [this, scene] (EntityID entity)
        {   
            Entity test(scene, entity);            

            auto& x = test.Get<TransformComponent>().Transforms.translation.x;
            auto name = test.Get<InfoComponent>().Name;
            LTB_INFO("Position: {}, name: {}", x, name);
            x += 1;
            // return std::ref(scene->get<TransformComponent>(entity).Transforms.translation.x);
            return x;
        });
        

        mLua.set_function("ApiTesting", [this, scene] (EntityID entity,Vector2 pos)
        {   
            // return scene->get<TransformComponent>(entity).Transforms.translation.x;
            // LTB_INFO("TESTING");
            Entity test(scene, entity);
            auto name = test.Get<InfoComponent>().Name;
            LTB_INFO("entity name: {}, test: {}", scene->get<InfoComponent>(entity).Name, name);  
            auto& mx = test.Get<TransformComponent>().Transforms.translation.x;
            auto& my = test.Get<TransformComponent>().Transforms.translation.y;   

            mx = pos.x;
            my = pos.y;   
            
        });

        // api function to check if key down
        mLua.set_function("ApiKeyDown", [this] (int32_t button)
        {
            // LTB_INFO("DOWN");
            return IsKeyDown(button);
        });        

        // api function to check if key pressed
        mLua.set_function("ApiKeyPressed", [this] (int32_t key)
        {
            // LTB_INFO("PRESSED");
            return IsKeyPressed(key);
        });

        // api function to destroy entity
        mLua.set_function("ApiDestroy", [this, scene] (EntityID entity)
        {
            // return if entity is dead!
            if(scene->valid(entity) == false) { return; }
                            
            // entity has rigidbody component                
            // if(scene->all_of<RigidBodyComponent>(entity)) 
            // {
            //     // destroy actor user data      
            //     auto& body = scene->get<RigidBodyComponent>(entity).RigidBody;     
            //     auto userData = static_cast<EntityID*>(body.Actor->userData);
            //     body.Actor->release();
            //     GEN_DELETE(userData);
            // } 

            // destroy collider material & shape
            // if(scene->all_of<ColliderComponent>(entity)) 
            // {
            //     // destroy actor user data      
            //     auto& collider = scene->get<ColliderComponent>(entity).Collider;     
            //     collider.Material->release();
            //     collider.Shape->release();
            // }                

            // entity has script component
            if(scene->all_of<ScriptComponent>(entity)) 
            {
                // call on destroy function
                scene->get<ScriptComponent>(entity).Instance->OnDestroy();     
            }

            // destroy entity from scene
            scene->destroy(entity);
        });
    }
}