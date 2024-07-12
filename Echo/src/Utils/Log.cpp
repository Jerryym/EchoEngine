#include "echopch.h"
#include "Log.h"

namespace Echo {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// 更改日志模式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// 初始化引擎端日志对象的颜色和等级
		s_CoreLogger = spdlog::stdout_color_mt("ECHO");
		s_CoreLogger->set_level(spdlog::level::trace);

		// 初始化客户端日志对象的颜色和等级
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}
