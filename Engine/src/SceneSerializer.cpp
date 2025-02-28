#include "ltbpch.h"
#include "SceneSerializer.h"
#include <yaml-cpp/yaml.h>
#include "ECS.h"
#include <fstream>

namespace YAML {
    template<>
	struct convert<Vector2>
	{
		static Node encode(const Vector2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Vector2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Vector3>
	{
		static Node encode(const Vector3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Vector3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Vector4>
	{
		static Node encode(const Vector4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Vector4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

    template<>
    struct convert<Matrix>
    {
        static Node encode(const Matrix& rhs){
            Node node;
            node.push_back(rhs.m0);
            node.push_back(rhs.m1);
            node.push_back(rhs.m2);
            node.push_back(rhs.m3);
            node.push_back(rhs.m4);
            node.push_back(rhs.m5);
            node.push_back(rhs.m6);
            node.push_back(rhs.m7);
            node.push_back(rhs.m8);
            node.push_back(rhs.m9);
            node.push_back(rhs.m10);
            node.push_back(rhs.m11);
            node.push_back(rhs.m12);
            node.push_back(rhs.m13);
            node.push_back(rhs.m14);
            node.push_back(rhs.m15);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, Matrix& rhs)
		{
			if (!node.IsSequence() || node.size() != 16)
				return false;

			rhs.m0 = node[0].as<float>();
			rhs.m1 = node[1].as<float>();
			rhs.m2 = node[2].as<float>();
			rhs.m3 = node[3].as<float>();
			rhs.m4 = node[4].as<float>();
			rhs.m5 = node[5].as<float>();
			rhs.m6 = node[6].as<float>();
			rhs.m7 = node[7].as<float>();
			rhs.m8 = node[8].as<float>();
			rhs.m9 = node[9].as<float>();
			rhs.m10 = node[10].as<float>();
			rhs.m11 = node[11].as<float>();
			rhs.m12 = node[12].as<float>();
			rhs.m13 = node[13].as<float>();
			rhs.m14 = node[14].as<float>();			
			rhs.m15 = node[15].as<float>();			
			return true;
		}
    };

    template<>
	struct convert<Color>
	{
		static Node encode(const Color& rhs)
		{
			Node node;
			node.push_back(rhs.r);
			node.push_back(rhs.g);
			node.push_back(rhs.b);
			node.push_back(rhs.a);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Color& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.r = node[0].as<unsigned char>();
			rhs.g = node[1].as<unsigned char>();
			rhs.b = node[2].as<unsigned char>();
			rhs.a = node[3].as<unsigned char>();
			return true;
		}
	};
}

namespace LTB {
    YAML::Emitter& operator<<(YAML::Emitter& out, const Vector2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Vector3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Vector4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

    YAML::Emitter& operator<<(YAML::Emitter& out, const Matrix& v){
        out << YAML::Flow;
        out << YAML::BeginSeq << v.m0 << v.m4 << v.m8 << v.m12 <<
        v.m1 << v.m5 << v.m9 << v.m13 
         << v.m2 << v.m6 << v.m10 << v.m14 << 
        v.m3 << v.m7 << v.m11 << v.m15 << YAML::EndSeq;

        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const Color& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.r << v.g << v.b << v.a << YAML::EndSeq;
		return out;
	}

    SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : mScene(scene){}

    static void SerializeEntity(YAML::Emitter& out, Entity entity){
        
        LTB_CORE_ASSERT(entity.Has<IDComponent>());

        out << YAML::BeginMap; // Entity
        out << YAML::Key << "Entity" << YAML::Value << entity.GetUUID();

        if(entity.Has<InfoComponent>()){

            out << YAML::Key << "InfoComponent";
            out << YAML::BeginMap; // InfoComponent

            auto& name = entity.Get<InfoComponent>().Name;
            out << YAML::Key << "Name" << YAML::Value << name;

            out << YAML::EndMap; // InfoComponent
        }

        if(entity.Has<TransformComponent>()){

            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap; // TransformComponent

            auto& tc = entity.Get<TransformComponent>().Transforms;
            out << YAML::Key << "Translation" << YAML::Value << tc.translation;
            out << YAML::Key << "Rotation" << YAML::Value << QuaternionToEuler(tc.rotation);
            out << YAML::Key << "Scale" << YAML::Value << tc.scale;

            out << YAML::EndMap; // TransformComponent
        }

        if(entity.Has<CameraComponent>()){

            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap; // CameraComponent

            auto& cameraComponent = entity.Get<CameraComponent>();
            auto& camera = cameraComponent.Camera;

            out << YAML::Key << "Camera";
            out << YAML::BeginMap; // Camera
            out << YAML::Key << "Position" << YAML::Value << camera.position;
            out << YAML::Key << "Target" << YAML::Value << camera.target;
            out << YAML::Key << "Up" << YAML::Value << camera.up;
            out << YAML::Key << "FOVY" << YAML::Value << camera.fovy;
            out << YAML::Key << "Projection" << YAML::Value << camera.projection;
            out << YAML::EndMap; // Camera

            out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;

            out << YAML::EndMap; // CAmeraComponent
        }

        if(entity.Has<Camera2DComponent>()){

            out << YAML::Key << "Camera2DComponent";
            out << YAML::BeginMap; // Camera2DComponent
            
            auto& camera2DComponent = entity.Get<Camera2DComponent>();
            auto& camera = camera2DComponent.Camera;

            out << YAML::Key << "Camera2D";
            out << YAML::BeginMap; // Camera2D
            out << YAML::Key << "Offset" << YAML::Value << camera.offset;
            out << YAML::Key << "Target" << YAML::Value << camera.target;
            out << YAML::Key << "Rotation" << YAML::Value << camera.rotation;
            out << YAML::Key << "Zoom" << YAML::Value << camera.zoom;
            out << YAML::EndMap; // Camera2D

            out << YAML::Key << "Primary" << YAML::Value << camera2DComponent.Primary;

            out << YAML::EndMap; // Camera2DComponent
        }

        if(entity.Has<ModelComponent>()){

            out << YAML::Key << "ModelComponent";
            out << YAML::BeginMap; // ModelComponent

            auto& modelComponent = entity.Get<ModelComponent>();
            auto& model = modelComponent.mModel;
            auto& box = modelComponent.Box;
            auto& color = modelComponent.color;
            
            out << YAML::Key << "Model";
            out << YAML::BeginMap; // Model
            out << YAML::Key << "Transform" << YAML::Value << model.transform;
            out << YAML::Key << "MeshCount" << YAML::Value << model.meshCount;
            out << YAML::Key << "MaterialCount" << YAML::Value << model.materialCount;
            //to do others
            out << YAML::EndMap; // Model

            out << YAML::Key << "Box";
            out << YAML::BeginMap; // Box
            out << YAML::Key << "min" << YAML::Value << box.min;
            out << YAML::Key << "max" << YAML::Value << box.max;
            out << YAML::EndMap; // Box

            out << YAML::Key << "Color" << YAML::Value << color;

            out << YAML::EndMap; // ModelComponent

        }

        if(entity.Has<SpriteComponent>()){

            out << YAML::Key << "SpriteComponent";
            out << YAML::BeginMap; // SpriteComponent
            
            auto& sprite = entity.Get<SpriteComponent>().mSprite;
            auto& texture = sprite.Texture;
            auto& box = sprite.Box;
            auto& color = sprite.color;

            out << YAML::Key << "Sprite";
            out << YAML::BeginMap; // Sprite

            out << YAML::Key << "Texture";
            out << YAML::BeginMap; // Texture
            out << YAML::Key << "ID" << YAML::Value << texture.id;
            out << YAML::Key << "Height" << YAML::Value << texture.height;
            out << YAML::Key << "Width" << YAML::Value << texture.width;
            out << YAML::Key << "Format" << YAML::Value << texture.format;
            out << YAML::Key << "MipMaps" << YAML::Value << texture.mipmaps;
            out << YAML::EndMap; // Texture

            out << YAML::Key << "Box";
            out << YAML::BeginMap; // Box
            out << YAML::Key << "X" << YAML::Value << box.x;
            out << YAML::Key << "Y" << YAML::Value << box.y;
            out << YAML::Key << "Width" << YAML::Value << box.width;
            out << YAML::Key << "Height" << YAML::Value << box.height;
            out << YAML::EndMap; // Box

            out << YAML::Key << "Color" << YAML::Value << color;

            out << YAML::EndMap; // sprite

            out << YAML::EndMap; // SpriteComponent
        }

        out << YAML::EndMap; // Entity

    }

    void SceneSerializer::Serialize(const std::string& filepath){
        YAML::Emitter out;
        out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        mScene->AllEntt<Entity>([this, &out] (auto entityID) {
            Entity entity = Entity(&mScene->mRegistry, entityID);
            if(!entity)
                return;
            SerializeEntity(out, entity);
        });

        out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
    }

    void SceneSerializer::SerializeRuntime(const std::string& filepath){
        //todo
    }

    bool SceneSerializer::Deserialize(const std::string& filepath){        
        YAML::Node data;
        try{
            data = YAML::LoadFile(filepath);
        }
        catch (YAML::ParserException e)
		{
            LTB_CORE_ERROR("{}", e.msg);
			return false;
		}

		if (!data["Scene"])
			return false;

        std::string sceneName = data["Scene"].as<std::string>();
		LTB_CORE_TRACE("Deserializing scene '{0}'", sceneName);

        auto entities = data["Entities"];

        if(entities){
            for(auto entity : entities){

                uint64_t uuid = entity["Entity"].as<uint64_t>();

                std::string name;

                auto infoComponent = entity["InfoComponent"];
                if(infoComponent)
                    name = infoComponent["Name"].as<std::string>();

                LTB_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

                Entity deserializedEntity = mScene->CreateEntityWithUUID(uuid, name);

                auto transformComponent = entity["TransformComponent"];
                if(transformComponent){
                    // Entities always have transforms
                    auto& tc = deserializedEntity.Get<TransformComponent>().Transforms;
                    auto quatern = QuaternionFromEuler(transformComponent["Rotation"].as<Vector3>().x,
                                                        transformComponent["Rotation"].as<Vector3>().y,
                                                        transformComponent["Rotation"].as<Vector3>().z);
                    tc.translation = transformComponent["Translation"].as<Vector3>();
					tc.rotation = quatern;
					tc.scale = transformComponent["Scale"].as<Vector3>();
                }

                auto cameraComponent = entity["CameraComponent"];
                if(cameraComponent){
                    auto& cc = deserializedEntity.Attach<CameraComponent>();
                    auto& cameraProps = cameraComponent["Camera"];

                    cc.Camera.position = cameraProps["Position"].as<Vector3>();
                    cc.Camera.target = cameraProps["Target"].as<Vector3>();
                    cc.Camera.up = cameraProps["Up"].as<Vector3>();
                    cc.Camera.fovy = cameraProps["FOVY"].as<float>();
                    cc.Camera.projection = cameraProps["Projection"].as<int>();

                    cc.Primary = cameraComponent["Primary"].as<bool>();
                }

                auto camera2DComponent = entity["Camera2DComponent"];
                if(camera2DComponent){
                    auto& cc = deserializedEntity.Attach<Camera2DComponent>();
                    auto& cameraProps = camera2DComponent["Camera2D"];

                    cc.Camera.offset = cameraProps["Offset"].as<Vector2>();
                    cc.Camera.target = cameraProps["Target"].as<Vector2>();
                    cc.Camera.rotation = cameraProps["Rotation"].as<float>();
                    cc.Camera.zoom = cameraProps["Zoom"].as<float>();

                    cc.Primary = camera2DComponent["Primary"].as<bool>();
                }

                auto modelComponent = entity["ModelComponent"];
                if(modelComponent){
                    auto& mc = deserializedEntity.Attach<ModelComponent>();
                    auto& modelProps = modelComponent["Model"];
                    auto& boxProps = modelComponent["Box"];
                    auto& colorProps = modelComponent["Color"];

                    mc.mModel.transform = modelProps["Transform"].as<Matrix>();
                    mc.mModel.meshCount = modelProps["MeshCount"].as<int>();
                    mc.mModel.materialCount = modelProps["MaterialCount"].as<int>();

                    mc.Box.max = boxProps["max"].as<Vector3>();
                    mc.Box.min = boxProps["min"].as<Vector3>();

                    mc.color = colorProps.as<Color>();
                }

                auto spriteComponent = entity["SpriteComponent"];
                if(spriteComponent){
                    auto& sc = deserializedEntity.Attach<SpriteComponent>().mSprite;
                    auto& spriteProps = spriteComponent["Sprite"];
                    auto& textureProps = spriteProps["Texture"];
                    auto& boxProps = spriteProps["Box"];
                    auto& colorProps = spriteProps["Color"];

                    sc.Texture.id = textureProps["ID"].as<unsigned int>();
                    sc.Texture.height = textureProps["Height"].as<int>();
                    sc.Texture.width = textureProps["Width"].as<int>();
                    sc.Texture.format = textureProps["Format"].as<int>();
                    sc.Texture.mipmaps = textureProps["MipMaps"].as<int>();

                    sc.Box.x = boxProps["X"].as<float>();
                    sc.Box.y = boxProps["Y"].as<float>();
                    sc.Box.width = boxProps["Width"].as<float>();
                    sc.Box.height = boxProps["Height"].as<float>();

                    // sc.color = colorProps.as<Color>();
                    // sc.color.r = colorProps.as<Color>().r;
                    // sc.color.g = colorProps.as<Color>().g;
                    // sc.color.b = colorProps.as<Color>().b;
                    // sc.color.a = colorProps.as<Color>().a;
                }
            }
        }

        return true;
    }

    bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		// Not implemented
		// FS_CORE_ASSERT(false);
		return false;
	}
}