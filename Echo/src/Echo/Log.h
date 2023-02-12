#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Echo {

	class ECHO_API Log
	{
	public:
		static void Init();

		/// <summary>
		/// 静态函数：获取引擎端日志
		/// </summary>
		/// <returns> 返回引擎端日志对象指针 </returns>
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/// <summary>
		/// 静态函数：获取客户端日志
		/// </summary>
		/// <returns> 返回客户端日志对象指针 </returns>
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;		// 引擎端日志对象(智能指针)
		static std::shared_ptr<spdlog::logger> s_ClientLogger;		// 客户端日志对象(智能指针)
	};

}

// Core log macros
#define ECHO_CORE_TRACE(...)		::Echo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ECHO_CORE_INFO(...)			::Echo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ECHO_CORE_WARN(...)			::Echo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ECHO_CORE_ERROR(...)		::Echo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ECHO_CORE_CRITICAL(...)		::Echo::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ECHO_CLIENT_TRACE(...)		::Echo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ECHO_CLIENT_INFO(...)		::Echo::Log::GetClientLogger()->info(__VA_ARGS__)
#define ECHO_CLIENT_WARN(...)		::Echo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ECHO_CLIENT_ERROR(...)		::Echo::Log::GetClientLogger()->error(__VA_ARGS__)
#define ECHO_CLIENT_CRITICAL(...)	::Echo::Log::GetClientLogger()->critical(__VA_ARGS__)


