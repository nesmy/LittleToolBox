#pragma once

///----------------------temp

//
// assert.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Defines the assert macro and related functionality.
//
#if defined _VCRT_BUILD && !defined _ASSERT_OK
    #error assert.h not for CRT internal use
#endif

#include <corecrt.h>

#pragma warning(push)
#pragma warning(disable: _UCRT_DISABLED_WARNINGS)
_UCRT_DISABLE_CLANG_WARNINGS
_CRT_BEGIN_C_HEADER

#if _CRT_HAS_C11

#define static_assert _Static_assert

#endif // _CRT_HAS_C11

#undef assert

#ifdef NDEBUG

    #define assert(expression) ((void)0)

#else

    _ACRTIMP void __cdecl _wassert(
        _In_z_ wchar_t const* _Message,
        _In_z_ wchar_t const* _File,
        _In_   unsigned       _Line
        );

    #define assert(expression) (void)(                                                       \
            (!!(expression)) ||                                                              \
            (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \
        )

#endif



_CRT_END_C_HEADER
_UCRT_RESTORE_CLANG_WARNINGS
#pragma warning(pop) // _UCRT_DISABLED_WARNINGS

//------------------------------------------------------

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <array>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <queue>
#include <bitset>
#include <random>
#include <fstream>
#include <assert.h>
#include <filesystem>
#include <cassert>
#include <raylib.h>
#include <rlImGui.h>