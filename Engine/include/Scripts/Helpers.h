#pragma once

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#define SOL_ALL_SAFETIES_ON 1
// #define SOL_SAFE_REFERENCES
// #define SOL_SAFE_USERTYPE 1
#include <sol/sol.hpp>
#include "Config.h"

namespace LTB {

}