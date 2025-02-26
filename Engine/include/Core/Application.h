#pragma once
#include "Config.h"
#include "Window.h"
#include "Renderer.h"
#include "Assets.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Event.h"

namespace LTB{

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
        void Update();
        void Render();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline ImGuiLayer& GetImGuiLayer() { return *mImGuiLayer;}
        inline static Application& Get() { return *sInstance;}
        inline Renderer& GetRenderer() { return *mRenderer;}
        inline AssetRegistry& GetAssets() { return *mAssets;}

        inline void Close(){
            mWindow->Close();
        }

    public:
         // create entity
        template <typename Entt, typename... Args>
        inline Entt CreateEntt(Args&&... args)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&mScene, std::forward<Args>(args)...));
        }

        // convert id to entity
        template<typename Entt>
        inline Entt ToEntt(EntityID entity)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&mScene, entity));
        }

        // loop through entities
        template<typename Entt, typename Comp, typename Task>
        inline void EnttView(Task&& task)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            mScene.view<Comp>().each([this, &task]
            (auto entity, auto& comp)
            {
                task(std::move(Entt(&mScene, entity)), comp);
            });
        }

        // loop through assets
        template<typename Task>
        inline void AssetView(Task&& task)
        {
            mAssets->View([&] (auto asset) { task(asset); });
        }

        // attach event callback
        template <typename Event, typename Callback>
        inline void AttachCallback(Callback&& callback)
        {
            mDispatcher.AttachCallback<Event>(std::move(callback), mLayerID);
        }

        // post event
        template <typename Event, typename... Args>
        inline void PostEvent(Args&&...args)
        {
            mDispatcher.PostEvent<Event>(std::forward<Args>(args)...);
        }

        // post task event
        template <typename Task>
        inline void PostTask(Task&& task)
        {
            mDispatcher.PostTask(std::move(task));
        }

        // detach callback
        template <typename Event>
        inline void DetachCallback()
        {
            mDispatcher.DetachCallback<Event>(mLayerID);
        }
    private:
        Scope<Window> mWindow;
        Scope<Renderer> mRenderer;
        Scope<AssetRegistry> mAssets;
        ImGuiLayer* mImGuiLayer;
        LayerStack mLayerStack;
        EntityRegistry mScene;
        EventDispatcher mDispatcher;
        uint32_t mLayerID;
    private:
        static Application* sInstance;
    };

    Application* CreateApplication();
}