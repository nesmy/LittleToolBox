#pragma once
#include "EnttInfo.h"


namespace LTB {

    struct InspectorWindow : public IWidget{
        inline InspectorWindow(EditorLayer* context): IWidget(context){
            mWidgets.push_back(context->CreateWidget<InfoControl>());
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