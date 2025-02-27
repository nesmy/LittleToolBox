#include "ltbpch.h"
#include "Application.h"

namespace LTB{

    Application* Application::sInstance = nullptr;

    Application::Application(){

        LTB_CORE_ASSERT(!sInstance, "Application already exists!");

        sInstance = this;
        mWindow = CreateScope<Window>();
        mWindow->Init(1600, 960, "Hello Window");        
        mAssets = CreateScope<AssetRegistry>();

        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);
    }

    Application::~Application(){

    }

    void Application::PushLayer(Layer* layer){        
        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer){
        mLayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run(){
        float DeltaTime = GetFrameTime();
        
        while(mWindow->ShouldClose()){
            mDispatcher.PollEvents(); 
            for(Layer* layer : mLayerStack){
                layer->OnUpdate(DeltaTime);
            }
            BeginDrawing();
            ClearBackground(BLACK);        

            mImGuiLayer->Begin();
            {
                for(Layer* layer: mLayerStack)
                    layer->OnImGuiRender();
            }
            mImGuiLayer->End();
            EndDrawing();
        }
    }

}