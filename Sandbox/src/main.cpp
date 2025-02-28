#include <LittleToolBox.h>
#include "GameLayer.h"

class Game : public LTB::Application{
public:
    Game(){
        PushLayer(new GameLayer());
    }

    ~Game(){

    }
};

LTB::Application* LTB::CreateApplication(){

    return new Game();
}