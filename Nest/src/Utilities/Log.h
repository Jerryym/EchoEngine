#pragma once

#include "NestCore.h"
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

		/// @brief 静态函数：获取客户端日志
		/// @return 
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;		// 框架端日志对象(智能指针)
		static std::shared_ptr<spdlog::logger> s_ClientLogger;		// 客户端日志对象(智能指针)
	};

	// Core log macros
	#define NEST_CORE_TRACE(...)		::Nest::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define NEST_CORE_INFO(...)			::Nest::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define NEST_CORE_WARN(...)			::Nest::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define NEST_CORE_ERROR(...)		::Nest::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define NEST_CORE_CRITICAL(...)		::Nest::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// Client log macros
	#define NEST_CLIENT_TRACE(...)		::Nest::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define NEST_CLIENT_INFO(...)		::Nest::Log::GetClientLogger()->info(__VA_ARGS__)
	#define NEST_CLIENT_WARN(...)		::Nest::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define NEST_CLIENT_ERROR(...)		::Nest::Log::GetClientLogger()->error(__VA_ARGS__)
	#define NEST_CLIENT_CRITICAL(...)	::Nest::Log::GetClientLogger()->critical(__VA_ARGS__)

}

