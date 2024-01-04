#pragma once

#include "Core/EngineCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace EchoEngine {

	/// @brief 引擎层日志
	class ECHOENGINE_API EngineLog
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
	#define ECHOENGINE_CORE_TRACE(...)			::EchoEngine::EngineLog::GetEngineLogger()->trace(__VA_ARGS__)
	#define ECHOENGINE_CORE_INFO(...)			::EchoEngine::EngineLog::GetEngineLogger()->info(__VA_ARGS__)
	#define ECHOENGINE_CORE_WARN(...)			::EchoEngine::EngineLog::GetEngineLogger()->warn(__VA_ARGS__)
	#define ECHOENGINE_CORE_ERROR(...)			::EchoEngine::EngineLog::GetEngineLogger()->error(__VA_ARGS__)
	#define ECHOENGINE_CORE_CRITICAL(...)		::EchoEngine::EngineLog::GetEngineLogger()->critical(__VA_ARGS__)

	// Client log macros
	#define ECHOENGINE_CLIENT_TRACE(...)		::EchoEngine::EngineLog::GetClientLogger()->trace(__VA_ARGS__)
	#define ECHOENGINE_CLIENT_INFO(...)			::EchoEngine::EngineLog::GetClientLogger()->info(__VA_ARGS__)
	#define ECHOENGINE_CLIENT_WARN(...)			::EchoEngine::EngineLog::GetClientLogger()->warn(__VA_ARGS__)
	#define ECHOENGINE_CLIENT_ERROR(...)		::EchoEngine::EngineLog::GetClientLogger()->error(__VA_ARGS__)
	#define ECHOENGINE_CLIENT_CRITICAL(...)		::EchoEngine::EngineLog::GetClientLogger()->critical(__VA_ARGS__)
}



