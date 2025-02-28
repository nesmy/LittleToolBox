#pragma once

#pragma once
#include "IControl.h"
#include "Application.h"

namespace LTB {

    extern const std::filesystem::path g_AssetPath;

    class SpriteControl : public IControl<SpriteComponent>{
    public:
        inline SpriteControl(EditorLayer* context) : IControl(context){
            SetTitle(ICON_FA_VIDEO "\tSprite");
        }

        inline void OnBody(EditorLayer* context, Entity& entity){

            auto& data = entity.template Get<SpriteComponent>().mSprite;
            InputRectangle("Box", &data.Box);            

            BeginInput("Texture");
            if(ImGui::ImageButtonEx((ImGuiID)10, (ImTextureID)&data.Texture, ImVec2(50, 50), 
                                                ImVec2(0, 1), ImVec2(1, 0), ImVec4(0, 0, 0, 1), ImVec4(1, 1, 1, 1))){
                
                ImGui::OpenPopup("spriteDrop");
            }

            if(ImGui::BeginPopup("spriteDrop")){

                Application::Get().AssetView([&] (auto* asset)
                {
                    if(asset->Type == AssetType::TEXTURE){
                        
                        if(ImGui::ImageButtonEx(asset->UID + 1, 
                        (ImTextureID)&static_cast<TextureAsset*>(asset)->Data, ImVec2(50, 50), ImVec2(0, 1), 
                        ImVec2(1, 0), ImVec4(0, 0, 0, 1), ImVec4(1, 1, 1, 1))){
                            data.Texture = static_cast<TextureAsset*>(asset)->Data;
                            ImGui::CloseCurrentPopup();
                        }
                    }
                });
                ImGui::EndPopup();
            }
            
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
                {
                    const wchar_t* path = (const wchar_t*)payload->Data;
                    // context->OpenScene(std::filesystem::path(g_AssetPath) / path);
                    std::filesystem::path newPath = std::filesystem::path(g_AssetPath) / path;
                    std::string filepath = newPath.generic_string();
                    Application::Get().AssetView([&] (auto* asset)
                    {
                        if(asset->Source == filepath){
                            data.Texture = static_cast<TextureAsset*>(asset)->Data;   
                            count++;                         
                        }
                        else if(count == 0){
                            auto newAsset = Application::Get().GetAssets().AddTexture(RandomU64(), 
                                                                                    filepath);
                            data.Texture = newAsset->Data;
                            count++;
                        }
                    });
                }
                ImGui::EndDragDropTarget();
            }


            EndInput();

            InputColor("Color", &data.color);
        }

        inline void OnMenu(EditorLayer* context, Entity& entity){
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tReset"))
            {
                entity.template Get<SpriteComponent>() = {};
            }
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tRemove"))
            {
                entity.template Detach<SpriteComponent>();
            }
        }
    private:
        ImTextureID mIcon;
        int count = 0;
    };
}