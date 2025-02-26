#pragma once
#include "EditorLayer.h"

namespace LTB {

    class MenuBarWindow : public IWidget 
    {
    public:
        inline MenuBarWindow(EditorLayer* context): IWidget(context)
        {

        }

        inline void OnShow(EditorLayer* context) override
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6, 6));           

            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("File")) 
                {
                    if (ImGui::MenuItem(ICON_FA_FILE " New Project", "Ctrl+N")) {}
                    if (ImGui::MenuItem(ICON_FA_FILE " Open Project", "Ctrl+O")) {
                        // context->Deserialize(*context->GetContext()->Assets, "Resources/Projects/savedassets.yaml");
                        // context->Deserialize(context->GetContext()->Scene, "Resources/Projects/savedscene.yaml");
                    }
                    if (ImGui::MenuItem(ICON_FA_STORE " Save Scene", "Ctrl+S")) {
                        // context->Serialize(*context->GetContext()->Assets, "Resources/Projects/savedassets.yaml");
                        // context->Serialize(context->GetContext()->Scene, "Resources/Projects/savedscene.yaml"); 
                    }
                    if (ImGui::MenuItem(ICON_FA_DOOR_CLOSED " Exit", "Alt+F4")) {
                        Application::Get().Close();    
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Scene")) 
                {
                    if (ImGui::MenuItem(ICON_FA_FORWARD " Add Entity")) 
                    {
                        auto entity = Application::Get().CreateEntt<Entity>();
                        // entity.template Attach<TransformComponent>();
                        entity.template Attach<InfoComponent>().Name = "New Entity";
                    }

                    if (ImGui::MenuItem(ICON_FA_FORWARD " Undo", "CTRL+Z")) {}
                    if (ImGui::MenuItem(ICON_FA_BACKWARD " Redo", "CTRL+Y")) {}
                    ImGui::Separator();
                    if (ImGui::MenuItem(ICON_FA_SCISSORS " Cut", "CTRL+X")) {}
                    if (ImGui::MenuItem(ICON_FA_CLONE " Copy", "CTRL+C")) {}
                    if (ImGui::MenuItem(ICON_FA_PASTE " Paste", "CTRL+V")) {}
                    if (ImGui::MenuItem(ICON_FA_TRASH " Delete", "Delete")) {}
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Settings")) 
                {
                    if (ImGui::MenuItem(ICON_FA_PALETTE " Theme")) {}
                    if (ImGui::MenuItem("3d/2d")) {
                        Application::Get().GetRenderer().SwitchCam();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Extra")) 
                {
                    if (ImGui::MenuItem(ICON_FA_INFO " Help", "Ctrl+H")) {}
                    if (ImGui::MenuItem(ICON_FA_QUESTION " About")) {}
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }
            ImGui::PopStyleVar();
        }
    };
}