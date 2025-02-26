#pragma once
#include "IControl.h"

namespace LTB {

    class TransformControl : public IControl<TransformComponent>{
    public:  
        inline TransformControl(EditorLayer* context): IControl(context)
        {
            SetTitle(ICON_FA_LOCATION_ARROW "\tTransform");
        }

        inline void OnBody(EditorLayer* context, Entity& entity) 
        {
            auto& data = entity.template Get<TransformComponent>().Transforms;
            InputVec3("Translate", &data.translation);
            // InputVec3("Rotation", &data.Rotation);
            InputVec3("Scale", &data.scale);    
        }

        inline void OnMenu(EditorLayer* context, Entity& entity) 
        {
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tReset")) 
            {
                entity.template Get<TransformComponent>() = {};
            }
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tRemove")) 
            {
                entity.template Detach<TransformComponent>();
            }     
        }
    };
}