#pragma once

#include "Layer.h"

namespace LTB {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();
    private:
    };
}