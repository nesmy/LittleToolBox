#pragma once
#include "IControl.h"

namespace LTB {

    class InfoControl : public IControl<InfoComponent>{
    public:
        inline InfoControl(EditorLayer* context): IControl(context)
        {
            SetTitle(ICON_FA_INFO "\tEntity");
        }

        inline void OnBody(EditorLayer* context, Entity& entity) 
        {
            auto& data = entity.template Get<InfoComponent>();
            InputText("Name", data.Name.data(), "Untitled", 64);
        }

        inline void OnMenu(EditorLayer* context, Entity& entity) 
        {
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tReset")) 
            {
                entity.template Get<InfoComponent>() = {};
            }        
        }
    private:
    };
}