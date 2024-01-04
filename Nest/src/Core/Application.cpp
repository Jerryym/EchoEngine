#include "nestpch.h"
#include "Application.h"

namespace Nest {

	Application* Application::s_Instance = nullptr;

	Application::Application(int& argc, char** argv)
		: QApplication(argc, argv)
	{
		NEST_CORE_ASSERT(s_Instance != nullptr, "Application already exists!");
		s_Instance = this;

		// 初始化框架的Log
		Nest::Log::InitLogger();
		NEST_CORE_WARN("Initialiazed Log!");
		NEST_CLIENT_INFO("Hello Nest FrameWork!");
	}

	void Application::SetMainWindow(QMainWindow* mainWindow)
	{
		s_Instance->m_Window.reset(mainWindow);
	}

}
