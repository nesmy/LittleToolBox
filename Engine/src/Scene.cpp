#include "ltbpch.h"
#include "Scene.h"
#include "ECS.h"
#include "Application.h"

namespace LTB {

    Scene::Scene(){                
        mGlobalCam.position = Vector3{1.0f, 1.0f, 1.0f};
        mGlobalCam.target = Vector3{4.0f, 1.0f, 4.0f};
        mGlobalCam.up = Vector3{0.0f, 1.0f, 0.0f};
        mGlobalCam.fovy = 45.0f;
        mGlobalCam.projection = CAMERA_PERSPECTIVE;

        mGlobalCam2D.zoom = 1.0f;

        Switch2d = false;
    }
    Scene::~Scene(){}

    Ref<Scene> Scene::Copy(Ref<Scene> other){
        Ref<Scene> newScene = CreateRef<Scene>();

        return newScene;
    }

    Entity Scene::CreateEntity(const std::string& name){

        return CreateEntityWithUUID(UUID(), name);
    }

    Entity Scene::CreateEntityWithUUID(UUID uuid,const std::string& name){

        Entity entity = CreateEntt<Entity>();
        entity.Attach<IDComponent>(uuid);
        auto& tag = entity.Attach<InfoComponent>().Name;
        tag = name.empty() ? "Entity" : name;
        entity.Attach<TransformComponent>();

        return entity;
    }

    void Scene::DestroyEntity(Entity entity){
        entity.Destroy();
    }

    void Scene::OnRuntimeStart(){}
    void Scene::OnRuntimeStop() {}

    void Scene::OnUpdateRuntime(float deltaTime) {}
    void Scene::OnUpdateEditor(float deltaTime) {          
        if(StopUpdate == false && Switch2d == false)
            UpdateCamera(&mGlobalCam, CAMERA_FREE);   

        if(StopUpdate == false && Switch2d == true)
            UpdateCamera2D(mGlobalCam2D); 
        GlobalCam();
        ClearBackground(RED);
        // Get ray and test against objects        
        ray = GetMouseRay(GetMousePosition(), mGlobalCam);

        EnttView<Entity, ModelComponent>([this] (auto entity, auto& comp){
            auto& transform = entity.template Get<TransformComponent>().Transforms;                        
            DrawModel(comp.mModel,transform.translation , 1.0f, WHITE);
            DrawBoundingBox(comp.Box, LIME);
        });

        EnttView<Entity, SpriteComponent>([this] (auto entity, auto& comp){
            auto& transform = entity.template Get<TransformComponent>().Transforms;
            DrawRectangleRec(comp.mSprite.Box, GREEN);
            DrawTextureV(comp.mSprite.Texture, {transform.translation.x, transform.translation.y}, WHITE);
            // LTB_CORE_INFO("x: {}, y: {}",transform.translation.x, transform.translation.y);
        });
        DrawGrid(10, 1.0);
        EndCam();
    }

    void Scene::DuplicateEntity(Entity entity){}

    void Scene::GlobalCam(){
        if(Switch2d){
            BeginMode2D(mGlobalCam2D);
        }
        else{
            BeginMode3D(mGlobalCam);
        }
    }

    void Scene::EndCam(){
        if(Switch2d){
            EndMode2D();
        }
        else{
            EndMode3D();
        }
    }

    void Scene::SwitchCam(){
        if(Switch2d)
            Switch2d = false;
        else if (Switch2d == false)
            Switch2d = true;
    }

    void Scene::UpdateCamera2D(Camera2D& camera)
    {
        float camera_speed = 5;
        if(IsKeyDown(KEY_LEFT)){
            camera.target.x -= camera_speed;
        }
        if(IsKeyDown(KEY_RIGHT)){
            camera.target.x += camera_speed;
        }
        if(IsKeyDown(KEY_UP)){
            camera.target.y -= camera_speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            camera.target.y += camera_speed;
        }
    }

    void Scene::BlockUpdate(bool update){
        StopUpdate = update;
    }
}