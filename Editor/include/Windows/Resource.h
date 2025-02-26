#pragma once
#include "EditorLayer.h"

namespace LTB {
    class ResourceWindow : public IWidget{
    public:	
        inline ResourceWindow(EditorLayer* context): IWidget(context)
        {
            m_IconImage = LoadTexture("Resources/Icons/asset.png");
            m_Icon = (ImTextureID)&m_IconImage;            
        }

        inline void OnShow(EditorLayer* context) override
        {
            if(ImGui::Begin(ICON_FA_FOLDER_OPEN "\tResources")) 
            {
                              
                int nbrColumn = (ImGui::GetContentRegionAvail().x/ASSET_SIZE) + 1;			
                int columnCounter = 1;
                int rowCounter = 1;
                if(ImGui::BeginTable("", nbrColumn))
                {

                Application::Get().AssetView([&] (auto* asset) 
                {	
                                                    
                    // show asset icon
                    iSClicked = ImGui::ImageButtonEx(asset->UID, 
                    m_Icon, ImVec2(ASSET_SIZE, ASSET_SIZE), ImVec2(0, 1), 
                    ImVec2(1, 0), ImVec4(0, 0, 0, 1), ImVec4(1, 1, 1, 1));
                    ImGui::Text(asset->Name.c_str());
                    ImGui::TableNextColumn();                    

                    if(iSClicked){
                        // m_Selected = asset->UID;                        
                    }
                        
                });

                ImGui::EndTable();
                }

            }
            ImGui::End();

            // if(iSClicked)
            //     Application::Get().PostEvent<ASelectEvent>(m_Selected);
            
            
        }

        // inline void OnSelect(AssetID asset) override
        // {
        //     m_Selected = asset;
        // }
        
    private:
        // Entity m_Selected;
        Texture2D m_IconImage;
        ImTextureID m_Icon;
        bool isSelected;
        bool iSClicked;
        // AssetID m_Selected;
    };
}