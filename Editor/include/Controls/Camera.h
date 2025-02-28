#pragma once
#include "IControl.h"

namespace LTB {

    class CameraControl : public IControl<CameraComponent>{
    public:
        inline CameraControl(EditorLayer* context) : IControl(context){
            SetTitle(ICON_FA_VIDEO "\tCamera");
        }

        inline void OnBody(EditorLayer* context, Entity& entity){

            auto& data = entity.template Get<CameraComponent>().Camera;
            InputVec3("Position", &data.position);
            InputVec3("Target", &data.target);
            InputVec3("Up", &data.up);
            InputFloat("FOVY", &data.fovy);
            InputFloat("Projection", &(float)data.projection);
        }

        inline void OnMenu(EditorLayer* context, Entity& entity){
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tReset"))
            {
                entity.template Get<CameraComponent>() = {};
            }
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tRemove"))
            {
                entity.template Detach<CameraComponent>();
            }
        }
    private:
    };
}