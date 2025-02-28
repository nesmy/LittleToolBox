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
        ClearBackground(RED);        

        MainScene->EnttView<LTB::Entity, LTB::SpriteComponent>([this] (auto entity, auto& comp){
            auto& transform = entity.template Get<LTB::TransformComponent>().Transforms;
            DrawRectangleRec(comp.mSprite.Box, GREEN);
            DrawTextureV(comp.mSprite.Texture, {transform.translation.x, transform.translation.y}, WHITE);
            // LTB_CORE_INFO("x: {}, y: {}",transform.translation.x, transform.translation.y);
        });
    }
private:
    LTB::Ref<LTB::Scene> MainScene;
};