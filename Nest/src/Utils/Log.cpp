#include "nestpch.h"
#include "Log.h"

namespace Nest {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::InitLogger(const QString& SCoreName, const QString& SClientName)
	{
		// 更改日志模式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// 初始化引擎端日志对象的颜色和等级
		s_CoreLogger = spdlog::stdout_color_mt(SCoreName.toStdString());
		s_CoreLogger->set_level(spdlog::level::trace);

		// 初始化客户端日志对象的颜色和等级
		s_ClientLogger = spdlog::stdout_color_mt(SClientName.toStdString());
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::InitLogger(QTextEdit* LogWidget, const QString& SCoreName, const QString& SClientName)
	{
		// 更改日志模式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// 初始化引擎端日志对象的颜色和等级
		s_CoreLogger = spdlog::qt_color_logger_mt(SCoreName.toStdString(), LogWidget, 500);

		// 初始化客户端日志对象的颜色和等级
		s_ClientLogger = spdlog::qt_color_logger_mt(SClientName.toStdString(), LogWidget, 500);
	}

}
