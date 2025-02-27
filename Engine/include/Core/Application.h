#pragma once
#include "Config.h"
#include "Window.h"
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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline ImGuiLayer& GetImGuiLayer() { return *mImGuiLayer;}
        inline static Application& Get() { return *sInstance;}        
        inline AssetRegistry& GetAssets() { return *mAssets;}

        inline void Close(){
            mWindow->Close();
        }

    public:        
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