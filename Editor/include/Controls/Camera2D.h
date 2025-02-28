#pragma once
#include "IControl.h"

namespace LTB {

    class Camera2DControl : public IControl<Camera2DComponent>{
    public:
        inline Camera2DControl(EditorLayer* context) : IControl(context){
            SetTitle(ICON_FA_VIDEO "\tCamera2D");
        }

        inline void OnBody(EditorLayer* context, Entity& entity){

            auto& data = entity.template Get<CameraComponent>().Camera;
            // InputVec3("Position", &data.position);
            // InputVec3("Target", &data.target);
            // InputVec3("Up", &data.up);
            // InputFloat("FOVY", &data.fovy);
            // InputFloat("Projection", &(float)data.projection);
        }

        inline void OnMenu(EditorLayer* context, Entity& entity){
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tReset"))
            {
                entity.template Get<Camera2DComponent>() = {};
            }
            if (ImGui::Selectable(ICON_FA_RECYCLE "\tRemove"))
            {
                entity.template Detach<Camera2DComponent>();
            }
        }
    private:
    };
}