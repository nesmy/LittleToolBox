#pragma once
#include "IControl.h"
#include "Application.h"

namespace LTB {

    class ScriptControl : public IControl<ScriptComponent>{
    public:
        inline ScriptControl(EditorLayer* context): IControl(context)
        {
            SetTitle(ICON_FA_INFO "\tScript");
        }

        inline ~ScriptControl(){
            // UnloadFileData(file);
        }

        inline void OnBody(EditorLayer* context, Entity& entity) 
        {
            // std::string test;
            // test.data()
            auto uuid = entity.template Get<ScriptComponent>().Script;            
            int size;            
            Application::Get().AssetView([&] (auto* asset)
            {
                if(uuid == asset->UUID && count == 0){
                    file = LoadFileData((const char*)asset->Source.data(), &size);
                    count++;
                }
            });
            
            // ImGui::InputTextMultiline("##", (char*)file, size, {300, 200});            
            
        }

        inline void OnMenu(EditorLayer* context, Entity& entity) 
        {
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tReset")) 
            {
                // entity.template Get<ScriptComponent>() = {};
            }        
        }
    private:
        int count = 0;
        unsigned char *file;
    };
}