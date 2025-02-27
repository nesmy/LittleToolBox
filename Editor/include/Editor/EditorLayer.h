#pragma once

#include "Layer.h"
#include "Widget.h"
#include "Scene.h"
#include "Framebuffer.h"

namespace LTB {

    class EditorLayer : public Layer {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float deltaTime) override;
        void OnImGuiRender() override;

        virtual void OnGuiStart();
        virtual void OnGuiFrame();

        void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

    public:
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

        inline const Scope<Framebuffer>& GetBuffer() const {
            return mBuffer;
        }

        inline Scene& GetActiveScene() { return *mActiveScene;}
        inline Ref<Scene>& GetActiveSceneRef() { return mActiveScene;}
        //temp
        std::filesystem::path mEditorScenePath;
    private:
        std::vector<Widget> mWindows;
        Ref<Scene> mActiveScene;

        enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState mSceneState = SceneState::Edit;
        Scope<Framebuffer> mBuffer;
    };
}