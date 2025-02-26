#pragma once
#include "EditorLayer.h"
#include "FA.h"

namespace LTB {
    class ViewportWindow : public IWidget {
    public:
        inline ViewportWindow(EditorLayer* context): IWidget(context)
        {
            // m_Frame = (ImTextureID)context->GetSceneFrame();
            mPlay = LoadTexture("Resources/Icons/PlayButton.png");
        }

        inline void OnShow(EditorLayer* context) override
        {
            
            bool Open = false;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));
            if(ImGui::Begin(ICON_FA_IMAGE "\tViewport", &Open, ImGuiWindowFlags_NoScrollbar))
            {

                auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
                auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
                auto viewportOffset = ImGui::GetWindowPos();
                m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
                m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

                m_ViewportFocused = ImGui::IsWindowFocused();
                m_ViewportHovered = ImGui::IsWindowHovered();                
                Application::Get().GetRenderer().BlockUpdate(!m_ViewportFocused && !m_ViewportHovered);

                ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
                m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
                //-------------------------------------

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
                ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
                auto& colors = ImGui::GetStyle().Colors;
                const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
                const auto& buttonActive = colors[ImGuiCol_ButtonActive];
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

                ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

                float size = ImGui::GetWindowHeight() - 4.0f;
                // Ref<Texture2D> icon = m_SceneState == SceneState::Edit ? m_IconPlay : m_IconStop;
                ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
                if (ImGui::ImageButton("##play",(ImTextureID)&mPlay, ImVec2(size, size)))
                {
                    // if (m_SceneState == SceneState::Edit)
                    //     OnScenePlay();
                    // else if (m_SceneState == SceneState::Play)
                    //     OnSceneStop();
                }
                ImGui::PopStyleVar(2);
                ImGui::PopStyleColor(3);
                ImGui::End();
                //-----------------------------------------------
                m_Frame = (ImTextureID)&Application::Get().GetRenderer().GetBuffer()->GetTexture().texture;
                // rlImGuiImageRenderTextureFit(&Application::Get().GetRenderer().GetBuffer()->GetTexture(), true);
                ImGui::Image(m_Frame, ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1,0});

                // get imgui io
                auto& io = ImGui::GetIO();

                if(ImGui::IsWindowHovered())
                {                        
                    
                }

                // context->m_ViewportFocused = ImGui::IsWindowFocused();
            }
            ImGui::End();
            ImGui::PopStyleVar();
        }

        // inline void OnSelect(Entity entity) override
        // {

        // }

    private:
        ImTextureID m_Frame;
        ImVec2 m_Viewport;
        Texture mPlay;
        ImVec2 m_ViewportBounds[2];
        ImVec2 m_ViewportSize;
        bool m_ViewportFocused = false, m_ViewportHovered = false;
    };
}