#include "ltbpch.h"
#include "Application.h"

namespace LTB{

    Application* Application::sInstance = nullptr;

    Application::Application(){

        LTB_CORE_ASSERT(!sInstance, "Application already exists!");

        sInstance = this;
        mWindow = CreateScope<Window>();
        mWindow->Init(1600, 960, "Hello Window");
        mRenderer = CreateScope<Renderer>();
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

        
        while(mWindow->ShouldClose()){
            Update();
            Render();
        }
    }

    void Application::Update(){
        mDispatcher.PollEvents();
        mRenderer->Update();        
    }

    void Application::Render(){
        BeginDrawing();
        ClearBackground(BLACK);

        mRenderer->GetBuffer()->Bind();
        mRenderer->GlobalCam();
        ClearBackground(RED);
        mRenderer->Render();
        mRenderer->EndCam();
        mRenderer->GetBuffer()->Unbind();

        mImGuiLayer->Begin();
        {
            for(Layer* layer: mLayerStack)
                layer->OnImGuiRender();
        }
        mImGuiLayer->End();
        EndDrawing();
    }
}