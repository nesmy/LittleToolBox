#pragma once

#include "Framebuffer.h"

namespace LTB {

    class Renderer{
    public:
        Renderer();
        ~Renderer();

        void Update();

        inline const Scope<Framebuffer>& GetBuffer() const {
            return mBuffer;
        }

        void GlobalCam();
        void EndCam();

        void SwitchCam();

        void BlockUpdate(bool update);
    private:
        Scope<Framebuffer> mBuffer;
        Camera3D mGlobalCam = {0};
        Camera2D mGlobalCam2D = {0};
        bool Switch2d;
        bool StopUpdate;
    };
}