#include "EditorLayer.h"
#include "Core/Application.h"
#include "MenuBar.h"
#include "Inspector.h"
#include "Hierarchy.h"
#include "Viewport.h"
#include "Resource.h"

namespace LTB {

    EditorLayer::EditorLayer()
        :Layer("EditorLayer"){}

    void EditorLayer::OnAttach(){
        Application::Get().AttachCallback<SelectEvent>([this] (auto e){
            for(auto& window : mWindows)
                window->OnSelect(Application::Get().ToEntt<Entity>(e.EnttID));
        });

        OnGuiStart();

        auto asset = Application::Get().GetAssets().AddTexture(RandomU64(), "Resources/Textures/Game/club/1_club.png");
        auto asset1 = Application::Get().GetAssets().AddTexture(RandomU64(), "Resources/Textures/Game/club/1_club.png");
        auto asset2 = Application::Get().GetAssets().AddTexture(RandomU64(), "Resources/Textures/Game/club/1_club.png");
        auto asset3 = Application::Get().GetAssets().AddTexture(RandomU64(), "Resources/Textures/Game/club/1_club.png");

        // auto cam = Application::Get().CreateEntt<Entity>();
        // cam.Attach<InfoComponent>().Name = "Cam";
        // cam.Attach<CameraComponent>();
        // auto& camTs = cam.Attach<TransformComponent>().Transforms;
        // camTs.translation = Vector3{0.0f};

        auto test = Application::Get().CreateEntt<Entity>();
        test.Attach<InfoComponent>().Name = "Test";
    }

    void EditorLayer::OnDetach(){

    }

    void EditorLayer::OnUpdate(){

    }

    void EditorLayer::OnImGuiRender(){
        // Set up the main viewport
        static auto viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowPos(viewport->Pos);

        static auto flags = ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_MenuBar;

        // if you want windows to dock to the viewport, call this.
    #ifdef IMGUI_HAS_DOCK
            ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
    #endif
        {
            // Set window style
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

            // Begin the main window
            ImGui::Begin("MainWindow", NULL, flags);
            {
                // Set up the main dockspace
                ImGui::DockSpace(ImGui::GetID("MainDockspace"), ImVec2(0, 0),
                ImGuiDockNodeFlags_PassthruCentralNode);
                ImGui::PopStyleColor();
                ImGui::PopStyleVar(3);

                // Iterate through each window in the vector and call OnShow
                for(auto& window : mWindows)
                {
                    window->OnShow(this);
                    window->OnShowAsset(this);
                }

                // m_ViewportFocused = ImGui::IsWindowFocused();

                // Interface update
                OnGuiFrame();
            }
            ImGui::End();
            }
    }

    void EditorLayer::OnGuiStart(){
        AttachWindow<MenuBarWindow>();
        AttachWindow<InspectorWindow>();
        AttachWindow<HierarchyWindow>();
        AttachWindow<ViewportWindow>();
        AttachWindow<ResourceWindow>();
    }

    void EditorLayer::OnGuiFrame(){

    }
}