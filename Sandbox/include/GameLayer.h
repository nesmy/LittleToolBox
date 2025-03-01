#pragma once

#include "Layer.h"
#include "Scene.h"
#include "SceneSerializer.h"
#include "ECS.h"
#include "raylib.h"

class GameLayer : public LTB::Layer{
public:
    GameLayer() = default;
    ~GameLayer() = default;

    inline void OnAttach() override{
        MainScene = LTB::CreateRef<LTB::Scene>();
        LTB::SceneSerializer serializer(MainScene);
        serializer.Deserialize("Resources/Saves/test.data");
    }

    inline void OnUpdate(float deltaTime) override{

    }

    inline void OnImGuiRender() override{
        MainScene->OnUpdateEditor(100);
    }
private:
    LTB::Ref<LTB::Scene> MainScene;
};