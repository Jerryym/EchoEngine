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
		NEST_CORE_INFO("Hello Nest FrameWork!");
	}

	Application::Application(int& argc, char** argv, bool InitLogger)
		: QApplication(argc, argv)
	{
		NEST_CORE_ASSERT(s_Instance != nullptr, "Application already exists!");
		s_Instance = this;

		if (InitLogger == true)
		{
			// 初始化框架的Log
			Nest::Log::InitLogger();
			NEST_CORE_WARN("Initialiazed Log!");
			NEST_CORE_INFO("Hello Nest FrameWork!");
		}
	}

	void Application::Run()
	{
		m_bRunning = true;
		m_Window->show();
	}

	void Application::SetMainWindow(QMainWindow* pMainWindow)
	{
		m_Window = std::unique_ptr<QMainWindow>(pMainWindow);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

}
