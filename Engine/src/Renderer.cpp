#include "ltbpch.h"
#include "Renderer/Renderer.h"

namespace LTB {

    Renderer::Renderer(){
        mBuffer = CreateScope<Framebuffer>(GetScreenWidth(), GetScreenHeight());

        mGlobalCam.position = Vector3{1.0f, 1.0f, 1.0f};
        mGlobalCam.target = Vector3{4.0f, 1.0f, 4.0f};
        mGlobalCam.up = Vector3{0.0f, 1.0f, 0.0f};
        mGlobalCam.fovy = 45.0f;
        mGlobalCam.projection = CAMERA_PERSPECTIVE;

        Switch2d = false;
    }

    Renderer::~Renderer(){

    }

    void Renderer::Update(){
        mBuffer->Resize();
        UpdateCamera(&mGlobalCam, CAMERA_FREE);
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
}