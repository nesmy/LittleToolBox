#pragma once
#include "Config.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace LTB {
    class Log {
    public:
        static void Init();

        // inline static Ref<spdlog::logger>& GetCoreLogger() { return sCoreLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger;}
        // inline static Ref<spdlog::logger>& GetClientLogger() { return sClientLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return sClientLogger;}
    private:
        static std::shared_ptr<spdlog::logger> sCoreLogger;
        static std::shared_ptr<spdlog::logger> sClientLogger;
    };
}


//core log macros
#define LTB_CORE_TRACE(...)              ::LTB::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LTB_CORE_INFO(...)               ::LTB::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LTB_CORE_WARN(...)               ::LTB::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LTB_CORE_ERROR(...)              ::LTB::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LTB_CORE_FATAL(...)              ::LTB::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log macros
#define LTB_TRACE(...)               ::LTB::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LTB_INFO(...)                ::LTB::Log::GetClientLogger()->info(__VA_ARGS__)
#define LTB_WARN(...)                ::LTB::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LTB_ERROR(...)               ::LTB::Log::GetClientLogger()->error(__VA_ARGS__)
#define LTB_FATAL(...)               ::LTB::Log::GetClientLogger()->fatal(__VA_ARGS__)