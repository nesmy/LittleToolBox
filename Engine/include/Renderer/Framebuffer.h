#pragma once

namespace LTB {

    class Framebuffer {
    public:
        Framebuffer(int width, int height);
        ~Framebuffer();

        void Resize();

        void Bind();
        void Unbind();

        RenderTexture &GetTexture() { return mViewTexture;}
    private:
        int mWidth, mHeight;
        RenderTexture mViewTexture;
    };
}