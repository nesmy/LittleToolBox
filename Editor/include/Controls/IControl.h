#pragma once
#include "EditorLayer.h"

namespace LTB {
    template <typename Component> 
    class IControl : public IWidget
    {
    public:
        inline virtual ~IControl() = default;

        inline IControl(EditorLayer* context): 
            IWidget(context)
        {}

        inline void OnSelect(Entity entity) override
        {
            m_Entity = entity;
        }

        // inline void OnSelect(AssetID asset) override
        // {
        //     m_Asset = asset;
        // }

        inline void SetTitle(const char* title) override
        {
            m_Title = title;
        }

        inline void OnShow(EditorLayer* context) override
        {
            if(!m_Entity.template Has<Component>()) { return; }            

            ImGui::PushID(m_Title); 
            static const auto flags = ImGuiTreeNodeFlags_DefaultOpen | 
            ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | 
            ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_AllowItemOverlap;

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.0f, 4.0f));       
            bool isCollapsed = ImGui::CollapsingHeader(m_Title, flags);          
            ImGui::PopStyleVar();

            // activate small font
            USE_SMALL_FONT();

            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);                    
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);                    

            if(InputButton(ICON_FA_GEAR)) 
            {
                ImGui::OpenPopup(m_Title);
            }           
            
            // Popup
            if (ImGui::BeginPopup(m_Title)) 
            {	
                ImGui::Text(m_Title);
                ImGui::Separator();
                OnMenu(context, m_Entity);
                ImGui::EndPopup();
            }   

            // Content
            if(isCollapsed) 
            {
                ImGui::Spacing();
                ImGui::Indent(5.0f);
                OnBody(context, m_Entity);
                ImGui::Spacing();
                ImGui::Unindent(5.0f);
            }

            ImGui::PopID();

            // switch back to regular font
            USE_REGULAR_FONT();
        };

        virtual void OnShowAsset(EditorLayer* context) {            

            ImGui::PushID(m_Title); 
            static const auto flags = ImGuiTreeNodeFlags_DefaultOpen | 
            ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | 
            ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_AllowItemOverlap;

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.0f, 4.0f));       
            bool isCollapsed = ImGui::CollapsingHeader(m_Title, flags);          
            ImGui::PopStyleVar();

            // activate small font
            USE_SMALL_FONT();

            // FS_CORE_INFO("{0}", m_Asset);

            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);                    
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);                    

            if(InputButton(ICON_FA_GEAR)) 
            {
                ImGui::OpenPopup(m_Title);
            }           
            
            // Popup
            if (ImGui::BeginPopup(m_Title)) 
            {	
                ImGui::Text(m_Title);
                ImGui::Separator();
                // OnMenuAsset(context, m_Asset);
                ImGui::EndPopup();
            }   

            // Content
            if(isCollapsed) 
            {
                ImGui::Spacing();
                ImGui::Indent(5.0f);
                // OnBodyAsset(context, m_Asset);
                ImGui::Spacing();
                ImGui::Unindent(5.0f);
            }

            ImGui::PopID();

            // switch back to regular font
            USE_REGULAR_FONT();
        }
            
    protected:
        inline void virtual OnMenu(EditorLayer*, Entity&) {}
        inline void virtual OnBody(EditorLayer*, Entity&) {}
        // inline void virtual OnMenuAsset(EditorLayer*, AssetID&) {}
        // inline void virtual OnBodyAsset(EditorLayer*, AssetID&) {}

    private:
        const char* m_Title;
        Entity m_Entity;
        // AssetID m_Asset;
    };
}