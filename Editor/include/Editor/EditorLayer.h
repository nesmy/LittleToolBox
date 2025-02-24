#pragma once

#include "Layer.h"
#include "Widget.h"

namespace LTB {

    class EditorLayer : public Layer {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnImGuiRender() override;

        virtual void OnGuiStart();
        virtual void OnGuiFrame();

        template<typename T, typename... Args>
        inline void AttachWindow(Args&&... args)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<IWidget, T>::value);
            auto window = std::make_unique<T>(this, std::forward<Args>(args)...);
            mWindows.push_back(std::move(window));
        }

        template<typename T, typename... Args>
        inline auto CreateWidget(Args&&... args)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<IWidget, T>::value);
            auto widget = std::make_unique<T>(this, std::forward<Args>(args)...);
            return widget;
        }
    private:
        std::vector<Widget> mWindows;
    };
}