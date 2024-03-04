#pragma once

#include "Core/EngineCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/qt_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Echo {

	/// @brief 引擎层日志
	class ECHO_API EchoLog
	{
	public:
		/// @brief 初始化Log
		static void InitLogger(QTextEdit* LogWidget);

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
	#define ECHO_CORE_TRACE(...)			::Echo::EchoLog::GetEngineLogger()->trace(__VA_ARGS__)
	#define ECHO_CORE_INFO(...)				::Echo::EchoLog::GetEngineLogger()->info(__VA_ARGS__)
	#define ECHO_CORE_WARN(...)				::Echo::EchoLog::GetEngineLogger()->warn(__VA_ARGS__)
	#define ECHO_CORE_ERROR(...)			::Echo::EchoLog::GetEngineLogger()->error(__VA_ARGS__)
	#define ECHO_CORE_CRITICAL(...)			::Echo::EchoLog::GetEngineLogger()->critical(__VA_ARGS__)

	// Client log macros
	#define ECHO_CLIENT_TRACE(...)			::Echo::EchoLog::GetClientLogger()->trace(__VA_ARGS__)
	#define ECHO_CLIENT_INFO(...)			::Echo::EchoLog::GetClientLogger()->info(__VA_ARGS__)
	#define ECHO_CLIENT_WARN(...)			::Echo::EchoLog::GetClientLogger()->warn(__VA_ARGS__)
	#define ECHO_CLIENT_ERROR(...)			::Echo::EchoLog::GetClientLogger()->error(__VA_ARGS__)
	#define ECHO_CLIENT_CRITICAL(...)		::Echo::EchoLog::GetClientLogger()->critical(__VA_ARGS__)
}



