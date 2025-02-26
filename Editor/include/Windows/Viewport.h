#pragma once
#include "EditorLayer.h"
#include "FA.h"

namespace LTB {
    class ViewportWindow : public IWidget {
    public:
        inline ViewportWindow(EditorLayer* context): IWidget(context)
        {
            // m_Frame = (ImTextureID)context->GetSceneFrame();
        }

        inline void OnShow(EditorLayer* context) override
        {
            bool Open = false;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));
            if(ImGui::Begin(ICON_FA_IMAGE "\tViewport", &Open, ImGuiWindowFlags_NoScrollbar))
            {
                
                rlImGuiImageRenderTextureFit(&Application::Get().GetRenderer().GetBuffer()->GetTexture(), true);

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
    };
}