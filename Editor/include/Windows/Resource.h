#pragma once
#include "EditorLayer.h"

namespace LTB {

    // Once we have projects, change this
	extern const std::filesystem::path g_AssetPath;

    class ResourceWindow : public IWidget{
    public:	
        inline ResourceWindow(EditorLayer* context): IWidget(context)
        {
            m_IconImage = LoadTexture("Resources/Icons/asset.png");
            mDirImage = LoadTexture("Resources/Icons/ContentBrowser/DirectoryIcon.png");
            m_Icon = (ImTextureID)&m_IconImage;
            mDirIcon = (ImTextureID)&mDirImage;     
            mCurrentDirectory = g_AssetPath;       
        }

        inline void OnShow(EditorLayer* context) override
        {
            if(ImGui::Begin(ICON_FA_FOLDER_OPEN "\tResources")) 
            {                                              

                if(mCurrentDirectory != std::filesystem::path(g_AssetPath)){
                    if(ImGui::Button("<-")){
                        mCurrentDirectory = mCurrentDirectory.parent_path();
                    }
                }

                static float padding = 16.0f;
                static float thumbnailSize = 128.0f;
                float cellSize = thumbnailSize + padding;

                float panelWidth = ImGui::GetContentRegionAvail().x;
                int columnCount = (int)(panelWidth / cellSize);
                if (columnCount < 1)
                    columnCount = 1;

                ImGui::Columns(columnCount, 0, false);

                for (auto& directoryEntry : std::filesystem::directory_iterator(mCurrentDirectory))
                {
                    const auto& path = directoryEntry.path();
                    auto relativePath = std::filesystem::relative(path, g_AssetPath);
                    std::string filenameString = relativePath.filename().string();
                    
                    ImGui::PushID(filenameString.c_str());
                    ImTextureID icon = directoryEntry.is_directory() ? mDirIcon : m_Icon;
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
                    ImGui::ImageButton(filenameString.c_str(),icon, { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

                    if (ImGui::BeginDragDropSource())
                    {
                        const wchar_t* itemPath = relativePath.c_str();
                        ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
                        ImGui::EndDragDropSource();
                    }

                    ImGui::PopStyleColor();
                    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    {
                        if (directoryEntry.is_directory())
                            mCurrentDirectory /= path.filename();

                    }
                    ImGui::TextWrapped(filenameString.c_str());

                    ImGui::NextColumn();

                    ImGui::PopID();
                }

                ImGui::Columns(1);

                // ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
                // ImGui::SliderFloat("Padding", &padding, 0, 32);

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
        Texture2D mDirImage;
        ImTextureID m_Icon;
        ImTextureID mDirIcon;
        bool isSelected;
        bool iSClicked;
        std::filesystem::path mCurrentDirectory;

        // AssetID m_Selected;
    };
}