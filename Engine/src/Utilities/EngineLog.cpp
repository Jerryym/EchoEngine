#include "echopch.h"
#include "EngineLog.h"
#include "Core/EchoApplication.h"
#include "GUI/Windows_MainWindow.h"
#include "GUI/ConsoleDockWidget.h"

namespace Echo {

	std::shared_ptr<spdlog::logger> EngineLog::s_EngineLogger;
	std::shared_ptr<spdlog::logger> EngineLog::s_ClientLogger;

	void EngineLog::InitLogger(QTextEdit* LogWidget)
	{
		// 更改日志模式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// 初始化引擎端日志对象的颜色和等级
		s_EngineLogger = spdlog::qt_color_logger_mt("ECHO", LogWidget, 500);

		// 初始化客户端日志对象的颜色和等级
		s_ClientLogger = spdlog::qt_color_logger_mt("APP", LogWidget, 500);
	}

}
