#pragma once
#include "EnttInfo.h"
#include "Transform.h"
#include "Camera.h"
#include "Camera2D.h"
#include "Sprite.h"
#include "Script.h"
#include "Model.h"

namespace LTB {

    struct InspectorWindow : public IWidget{
        inline InspectorWindow(EditorLayer* context): IWidget(context){
            mWidgets.push_back(context->CreateWidget<InfoControl>());
            mWidgets.push_back(context->CreateWidget<TransformControl>());
            mWidgets.push_back(context->CreateWidget<CameraControl>());
            mWidgets.push_back(context->CreateWidget<Camera2DControl>());
            mWidgets.push_back(context->CreateWidget<SpriteControl>());
            mWidgets.push_back(context->CreateWidget<ScriptControl>());
            mWidgets.push_back(context->CreateWidget<ModelControl>());
        }

        inline void OnShow(EditorLayer* context) override{
            if(ImGui::Begin(ICON_FA_CIRCLE_INFO "\tInspector")) 
            {
                for(auto& widget : mWidgets)			
                    widget->OnShow(context);
                
            }
            ImGui::End();
        }

        inline void OnSelect(Entity entity) override 
        {
            for(auto& widget : mWidgets)			
                widget->OnSelect(entity);            					
        }
    private:
        std::vector<Widget> mWidgets;
    };
}