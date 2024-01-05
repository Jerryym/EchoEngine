#include "enginepch.h"
#include "EngineLog.h"

namespace Echo {

	std::shared_ptr<spdlog::logger> EngineLog::s_EngineLogger;
	std::shared_ptr<spdlog::logger> EngineLog::s_ClientLogger;

	void EngineLog::InitLogger()
	{
		// 更改日志模式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// 初始化引擎端日志对象的颜色和等级
		s_EngineLogger = spdlog::stdout_color_mt("ECHOENGINE");
		s_EngineLogger->set_level(spdlog::level::trace);

		// 初始化客户端日志对象的颜色和等级
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}
