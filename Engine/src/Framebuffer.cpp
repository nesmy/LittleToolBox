#include "ltbpch.h"
#include "Renderer/Framebuffer.h"


namespace LTB {

    Framebuffer::Framebuffer(int width, int height) : mWidth(width), mHeight(height){

        mViewTexture = LoadRenderTexture(mWidth, mHeight);
    }

    Framebuffer::~Framebuffer(){
        UnloadRenderTexture(mViewTexture);
    }

    void Framebuffer::Resize(){
        if(IsWindowResized()){
            UnloadRenderTexture(mViewTexture);
            mViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        }
    }

    void Framebuffer::Bind(){
        BeginTextureMode(mViewTexture);
    }

    void Framebuffer::Unbind(){
        EndTextureMode();
    }
}