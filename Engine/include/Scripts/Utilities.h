#pragma once

#include "Helpers.h"

namespace LTB {

    class Script{
    public:
        // script handle constructor
        inline Script(sol::table handle, const std::string& name):mHandle(handle), mName(name){}

        // callback for window resize event
        inline void OnResize(int32_t width, int32_t height){
            if(mHandle.valid())
                mHandle["OnResize"](mHandle, width, height);
        }

        // callback for key down event
        inline void OnKeyDown(int button){
            if(mHandle.valid())
                mHandle["OnKeyDown"](mHandle, button);
            
        }

        // callback for key pressed event
        inline void OnKeyPressed(int button){
            if(mHandle.valid())
                mHandle["OnKeyPressed"](mHandle, button);
        }

        // callback to update script
        inline void OnUpdate(float dt){
            if(mHandle.valid())
                mHandle["OnUpdate"](mHandle, dt);            
        }

        // callback to destroy entity
        inline void OnDestroy(){
            if(mHandle.valid())
                mHandle["OnDestroy"](mHandle);
        }

        // callback to start script
        inline void OnStart(){
            if(mHandle.valid())
                mHandle["OnStart"](mHandle);
        }

        // return script name
        inline const std::string& Name(){
            return mName;
        }

        // check if valid
        inline bool Valid(){
            return mHandle.valid();
        }
    private:
        friend class ScriptContext;
        sol::table mHandle;
        std::string mName;
    };

    using LuaScript = std::unique_ptr<Script>;
}