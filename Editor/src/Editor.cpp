#include <LittleToolBox.h>
#include "EditorLayer.h"

namespace LTB{

    class Editor : public Application{
    public:
        Editor(){
            PushLayer(new EditorLayer());
        }

        ~Editor(){

        }
    private:
    };
}

LTB::Application* LTB::CreateApplication(){

    return new Editor();
}