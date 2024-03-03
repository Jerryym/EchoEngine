#include "nestpch.h"
#include "Log.h"

namespace Nest {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::InitLogger()
	{
		// 更改日志模式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// 初始化引擎端日志对象的颜色和等级
		s_CoreLogger = spdlog::stdout_color_mt("NEST");
		s_CoreLogger->set_level(spdlog::level::trace);
	}

}
