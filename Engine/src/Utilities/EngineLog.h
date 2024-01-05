#pragma once

#include "Core/EngineCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Echo {

	/// @brief 引擎层日志
	class ECHO_API EngineLog
	{
	public:
		/// @brief 初始化Log
		static void InitLogger();

		/// @brief 静态函数：获取引擎端日志
		/// @return 
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }

		/// @brief 静态函数：获取客户端日志
		/// @return 
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;		// 引擎端日志对象(智能指针)
		static std::shared_ptr<spdlog::logger> s_ClientLogger;		// 客户端日志对象(智能指针)
	};

	// Engine log macros
	#define ECHOENGINE_CORE_TRACE(...)			::Echo::EngineLog::GetEngineLogger()->trace(__VA_ARGS__)
	#define ECHOENGINE_CORE_INFO(...)			::Echo::EngineLog::GetEngineLogger()->info(__VA_ARGS__)
	#define ECHOENGINE_CORE_WARN(...)			::Echo::EngineLog::GetEngineLogger()->warn(__VA_ARGS__)
	#define ECHOENGINE_CORE_ERROR(...)			::Echo::EngineLog::GetEngineLogger()->error(__VA_ARGS__)
	#define ECHOENGINE_CORE_CRITICAL(...)		::Echo::EngineLog::GetEngineLogger()->critical(__VA_ARGS__)

	// Client log macros
	#define ECHOENGINE_CLIENT_TRACE(...)		::Echo::EngineLog::GetClientLogger()->trace(__VA_ARGS__)
	#define ECHOENGINE_CLIENT_INFO(...)			::Echo::EngineLog::GetClientLogger()->info(__VA_ARGS__)
	#define ECHOENGINE_CLIENT_WARN(...)			::Echo::EngineLog::GetClientLogger()->warn(__VA_ARGS__)
	#define ECHOENGINE_CLIENT_ERROR(...)		::Echo::EngineLog::GetClientLogger()->error(__VA_ARGS__)
	#define ECHOENGINE_CLIENT_CRITICAL(...)		::Echo::EngineLog::GetClientLogger()->critical(__VA_ARGS__)
}



