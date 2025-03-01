#pragma once
#include "EditorLayer.h"
#include "SceneSerializer.h"
#include <ImGuiFileDialog.h>

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
                    if (ImGui::MenuItem(ICON_FA_FILE " New Scene", "Ctrl+N")) {
                        context->NewScene();
                    }
                    if (ImGui::MenuItem(ICON_FA_FILE " Open Scene", "Ctrl+O")) {                        
                        context->OpenScene();
                    }
                    if (ImGui::MenuItem(ICON_FA_STORE " Save Scene", "Ctrl+S")) {
                        context->SaveScene();
                    }
                    if (ImGui::MenuItem(ICON_FA_STORE " Save Scene As", "Ctrl+Shift+S")) {
                        context->SaveSceneAs();
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
                        context->GetActiveScene().CreateEntity();
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
                        context->GetActiveScene().SwitchCam();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Extra")) 
                {
                    if (ImGui::MenuItem(ICON_FA_INFO " Help", "Ctrl+H")) {}
                    if (ImGui::MenuItem(ICON_FA_QUESTION " About")) {}
                    ImGui::EndMenu();
                }
                // drawGui();
                ImGui::EndMainMenuBar();
            }
            
            ImGui::PopStyleVar();        
        }
    };
}