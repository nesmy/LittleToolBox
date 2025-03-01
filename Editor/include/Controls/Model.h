#pragma once
#include "IControl.h"
#include "Application.h"
#include "Framebuffer.h"

namespace LTB {

    extern const std::filesystem::path g_AssetPath;

    class ModelControl : public IControl<ModelComponent>
    {
    public:  
        inline ModelControl(EditorLayer* context): IControl(context)
        {
            SetTitle(ICON_FA_LOCATION_ARROW "\tModel");
            ModelBuffer = CreateScope<Framebuffer>(GetScreenWidth(), GetScreenHeight());
            ModelsViewBuffer = CreateScope<Framebuffer>(GetScreenWidth(), GetScreenHeight());
            cam.position = Vector3{1.0f, 1.0f, 1.0f};
            cam.target = Vector3{0.0f, 0.0f, 0.0f};
            cam.up = Vector3{0.0f, 1.0f, 0.0f};
            cam.fovy = 45.0f;
            cam.projection = CAMERA_PERSPECTIVE;
        }

        inline void OnBody(EditorLayer* context, Entity& entity) 
        {
            ModelBuffer->Resize();
            ModelsViewBuffer->Resize();
            auto& model = entity.template Get<ModelComponent>().mModel;

            ModelBuffer->Bind();
            ClearBackground(GREEN);
            BeginMode3D(cam);
            DrawModel(model,Vector3Zero() , 1.0f, WHITE);
            EndMode3D();
            ModelBuffer->Unbind();
            
            // auto& tex = image.Data.materials[0].maps[0].texture;
            BeginInput("Model");
            // ImGui::Image((ImTextureID)&ModelBuffer->GetTexture().texture, ImVec2{100, 100}, ImVec2{0, 1}, ImVec2{1,0});
            if(ImGui::ImageButton("##", (ImTextureID)&ModelBuffer->GetTexture().texture, {100, 100}, { 0, 1 }, { 1, 0 })){
                ImGui::OpenPopup("modelDrop");
            }

            if(ImGui::BeginPopup("modelDrop")){

                Application::Get().AssetView([&] (auto* asset)
                {
                    if(asset->Type == AssetType::MODEL){

                        ModelsViewBuffer->Bind();
                        ClearBackground(GREEN);
                        BeginMode3D(cam);
                        DrawModel(static_cast<ModelAsset*>(asset)->Data,Vector3Zero() , 1.0f, WHITE);
                        EndMode3D();
                        ModelsViewBuffer->Unbind();
                        
                        if(ImGui::ImageButtonEx(asset->UUID + 1, 
                        (ImTextureID)&ModelsViewBuffer->GetTexture().texture, ImVec2(50, 50), ImVec2(0, 1), 
                        ImVec2(1, 0), ImVec4(0, 0, 0, 1), ImVec4(1, 1, 1, 1))){
                            model = static_cast<ModelAsset*>(asset)->Data;
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
                            model = static_cast<ModelAsset*>(asset)->Data;   
                            count++;                         
                        }
                        else if(count == 0){
                            auto newAsset = Application::Get().GetAssets().AddModel(RandomU64(), 
                                                                                    filepath);
                            model = newAsset->Data;
                            count++;
                        }
                    });
                }
                ImGui::EndDragDropTarget();
            }

            EndInput();

            // std::string width = std::to_string(tex.width);
            // ImGui::InputTextMultiline
            if(ImGui::Button("Testing", {10, 10})){
                int size;
                // auto file = LoadFileData("Data/Script/TestScript.lua", &size);

                // LTB_INFO("{}", std::string((char*)file));                
            }

            // InputText("Name", image.Name.c_str());
            // FS_INFO("{0}", image.Name);
            // ImGui::Text(image.Name.c_str());
        }

        inline void OnMenuAsset(EditorLayer* context) 
        {
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tReset")) 
            {
                // entity.template Get<TransformComponent>() = {};
            }
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tRemove")) 
            {
                // entity.template Detach<TransformComponent>();
            }     
        }
    private:
        Scope<Framebuffer> ModelBuffer;
        Scope<Framebuffer> ModelsViewBuffer;
        Camera3D cam;
        int count = 0;
    };
}