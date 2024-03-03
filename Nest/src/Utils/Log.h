#pragma once

#include "Core/NestCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Nest {

	class NEST_API Log
	{
	public:
		/// @brief 初始化Log
		static void InitLogger();

		/// @brief 静态函数：获取框架端日志
		/// @return 
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;		// 框架端日志对象(智能指针)
	};

	// Core log macros
	#define NEST_CORE_TRACE(...)		::Nest::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define NEST_CORE_INFO(...)			::Nest::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define NEST_CORE_WARN(...)			::Nest::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define NEST_CORE_ERROR(...)		::Nest::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define NEST_CORE_CRITICAL(...)		::Nest::Log::GetCoreLogger()->critical(__VA_ARGS__)

}

