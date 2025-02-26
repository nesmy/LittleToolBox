#pragma once

#include <raylib.h>

namespace LTB{
    class Window {
    public:
        Window(){}

        inline bool Init(int width, int height, const char* title){
            InitWindow(width, height, title);
            SetTargetFPS(144);
            SetExitKey(KEY_NULL);    
            mClose = false;        
            return true;
        }

        inline bool ShouldClose(){
            return !WindowShouldClose() && !mClose;
        }

        inline void Close(){
            mClose = true;            
        }

        ~Window(){
            CloseWindow();
        }
    private:
        bool mClose;
    };
}