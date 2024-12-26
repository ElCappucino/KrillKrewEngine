#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Krill
{
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log
#define KK_CORE_TRACE(...) :: Krill::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KK_CORE_INFO(...) :: Krill::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KK_CORE_WARN(...) :: Krill::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KK_CORE_ERROR(...) :: Krill::Log::GetCoreLogger()->error(__VA_ARGS__)
// #define KK_CORE_FATAL(...) :: Krill::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log
#define KK_TRACE(...) :: Krill::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KK_INFO(...) :: Krill::Log::GetClientLogger()->info(__VA_ARGS__)
#define KK_WARN(...) :: Krill::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KK_ERROR(...) :: Krill::Log::GetClientLogger()->error(__VA_ARGS__)
// #define KK_FATAL(...) :: Krill::Log::GetClientLogger()->fatal(__VA_ARGS__)