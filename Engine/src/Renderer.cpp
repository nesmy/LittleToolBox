#include "ltbpch.h"
#include "Renderer/Renderer.h"
#include "Application.h"
#include "ECS.h"
#include "rlgl.h"

namespace LTB {

    Renderer::Renderer(){
        mBuffer = CreateScope<Framebuffer>(GetScreenWidth(), GetScreenHeight());

        mGlobalCam.position = Vector3{1.0f, 1.0f, 1.0f};
        mGlobalCam.target = Vector3{4.0f, 1.0f, 4.0f};
        mGlobalCam.up = Vector3{0.0f, 1.0f, 0.0f};
        mGlobalCam.fovy = 45.0f;
        mGlobalCam.projection = CAMERA_PERSPECTIVE;

        mGlobalCam2D.zoom = 1.0f;

        Switch2d = false;
        StopUpdate = false;                
    }

    Renderer::~Renderer(){

    }

    void Renderer::Update(){
        mBuffer->Resize();
        if(StopUpdate == false)
            UpdateCamera(&mGlobalCam, CAMERA_FREE);
    }


    void Renderer::Render(){

        // Display information about closest hit
        RayCollision collision = { 0 };
        char *hitObjectName = "None";
        collision.distance = FLT_MAX;
        collision.hit = false;
        Color cursorColor = WHITE;

        // Get ray and test against objects        
        ray = GetMouseRay(GetMousePosition(), mGlobalCam);

        Application::Get().EnttView<Entity, ModelComponent>([this] (auto entity, auto& comp){
            auto& transform = entity.template Get<TransformComponent>().Transforms;                        
            DrawModel(comp.mModel,transform.translation , 1.0f, WHITE);
            DrawBoundingBox(comp.Box, LIME);
        });

        Application::Get().EnttView<Entity, SpriteComponent>([this] (auto entity, auto& comp){
            auto& transform = entity.template Get<TransformComponent>().Transforms;
            DrawRectangleRec(comp.mSprite.Box, GREEN);
            DrawTextureV(comp.mSprite.Texture, {transform.translation.x, transform.translation.y}, WHITE);
            // LTB_CORE_INFO("x: {}, y: {}",transform.translation.x, transform.translation.y);
        });
        DrawGrid(10, 1.0);
    }

    void Renderer::GlobalCam(){
        if(Switch2d){
            BeginMode2D(mGlobalCam2D);
        }
        else{
            BeginMode3D(mGlobalCam);
        }
    }

    void Renderer::EndCam(){
        if(Switch2d){
            EndMode2D();
        }
        else{
            EndMode3D();
        }
    }

    void Renderer::SwitchCam(){
        if(Switch2d)
            Switch2d = false;
        else if (Switch2d == false)
            Switch2d = true;
    }

    void Renderer::BlockUpdate(bool update){
        StopUpdate = update;
    }
}