#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Echo {

	class ECHO_API Log
	{
	public:
		/// @brief 初始化日志系统
		static void Init();

		/// @brief 获取引擎端日志
		/// @return 
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/// @brief 获取客户端日志
		/// @return 
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		/// @brief 引擎端日志对象(智能指针)
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		/// @brief 客户端日志对象(智能指针)
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
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
