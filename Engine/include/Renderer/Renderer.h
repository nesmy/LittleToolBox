#pragma once

#include "Framebuffer.h"

#define FLT_MAX     340282346638528859811704183484516925440.0f 

namespace LTB {

    class Renderer{
    public:
        Renderer();
        ~Renderer();

        void Update();

        void Render();

        inline const Scope<Framebuffer>& GetBuffer() const {
            return mBuffer;
        }

        void GlobalCam();
        void EndCam();

        void SwitchCam();

        void BlockUpdate(bool update);

    public:       
        Camera3D &GetCam() { return mGlobalCam;}
        Camera2D &GetCam2D() { return mGlobalCam2D;}
        bool &Is2D() { return Switch2d;}
    private:
        Scope<Framebuffer> mBuffer;
        Camera3D mGlobalCam = {0};
        Camera2D mGlobalCam2D = {0};
        Ray ray = {0};
        BoundingBox testBox;
        bool Switch2d;
        bool StopUpdate;
    };
}