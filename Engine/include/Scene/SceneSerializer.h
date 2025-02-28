#pragma once

#include "Scene.h"

namespace YAML{
    class Node;
}

namespace LTB {

    class SceneSerializer{
    public:
        SceneSerializer(const Ref<Scene>& scene);
        void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);
    private:
        void DeserializeEntities(YAML::Node& data);
        void DeserializeAssets(YAML::Node& data);
        Ref<Scene> mScene;
    };
}