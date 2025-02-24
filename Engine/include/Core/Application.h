#pragma once
#include "Config.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"

namespace LTB{

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline ImGuiLayer& GetImGuiLayer() { return *mImGuiLayer;}

        inline static Application& Get() { return *sInstance;}

    public:
         // create entity
        template <typename Entt, typename... Args>
        inline Entt CreateEntt(Args&&... args)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&m_Scene, std::forward<Args>(args)...));
        }

        // convert id to entity
        template<typename Entt>
        inline Entt ToEntt(EntityID entity)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&m_Scene, entity));
        }

        // loop through entities
        template<typename Entt, typename Comp, typename Task>
        inline void EnttView(Task&& task)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            m_Scene.view<Comp>().each([this, &task]
            (auto entity, auto& comp)
            {
                task(std::move(Entt(&m_Scene, entity)), comp);
            });
        }

        // loop through entities
        // template<typename Task>
        // inline void AssetView(Task&& task)
        // {
        //     m_Assets->View([&] (auto asset) { task(asset); });
        // }
    private:
        Scope<Window> mWindow;
        ImGuiLayer* mImGuiLayer;
        LayerStack mLayerStack;
    private:
        static Application* sInstance;
    };

    Application* CreateApplication();
}