#pragma once
#include "Utilities.h"
#include "ECS.h"

namespace LTB {

    class ScriptContext{
    public:
        ScriptContext(EntityRegistry* scene);
        bool AttachScript(Entity& entity, const std::string& name);
        std::string LoadScript(const std::string& filepath);
    private:
        void SetApiFunctions(EntityRegistry* scene);
        void InitVariable();
    private:
        sol::state mLua;
    };
}