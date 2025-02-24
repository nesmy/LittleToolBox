#include "Application.h"

namespace LTB{

    Application* Application::sInstance = nullptr;

    Application::Application(){

        LTB_CORE_ASSERT(!sInstance, "Application already exists!");

        sInstance = this;
        mWindow = CreateScope<Window>();

        mWindow->Init(500, 500, "Hello Window");

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

        while(mWindow->ShouldClose()){
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