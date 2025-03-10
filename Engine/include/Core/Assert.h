#pragma once

#include "Log.h"
#include <filesystem>

#ifdef LTB_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define LTB_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LTB##type##ERROR(msg, __VA_ARGS__); LTB_DEBUGBREAK(); } }
	#define LTB_INTERNAL_ASSERT_WITH_MSG(type, check, ...) LTB_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define LTB_INTERNAL_ASSERT_NO_MSG(type, check) LTB_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", LTB_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define LTB_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define LTB_INTERNAL_ASSERT_GET_MACRO(...) LTB_EXPAND_MACRO( LTB_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LTB_INTERNAL_ASSERT_WITH_MSG, LTB_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define LTB_ASSERT(...) LTB_EXPAND_MACRO( LTB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define LTB_CORE_ASSERT(...) LTB_EXPAND_MACRO( LTB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define LTB_ASSERT(...)
	#define LTB_CORE_ASSERT(...)
#endif