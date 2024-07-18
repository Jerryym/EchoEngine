#include "echopch.h"
#include "Application.h"

namespace Echo {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ECHO_CORE_ASSERT(s_Instance != nullptr, "Application already exists!");
		s_Instance = this;

		//创建主窗口
		m_MainWindow = std::unique_ptr<MainWindow>(MainWindow::CreateMainWindow());
	}

	void Application::Run()
	{
		m_bRunning = true;
		while (m_bRunning)
		{
			//更新主窗口
			m_MainWindow->OnUpdate();
		}
	}

}
