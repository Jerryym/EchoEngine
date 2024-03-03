#include "echopch.h"
#include "EchoLog.h"

namespace Echo {

	std::shared_ptr<spdlog::logger> EchoLog::s_EngineLogger;
	std::shared_ptr<spdlog::logger> EchoLog::s_ClientLogger;

	void EchoLog::InitLogger(QTextEdit* LogWidget)
	{
		// 更改日志模式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// 初始化引擎端日志对象的颜色和等级
		s_EngineLogger = spdlog::qt_color_logger_mt("ECHO", LogWidget, 500);

		// 初始化客户端日志对象的颜色和等级
		s_ClientLogger = spdlog::qt_color_logger_mt("APP", LogWidget, 500);
	}

}
