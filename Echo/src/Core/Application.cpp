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
		m_MainWindow->SetEventCallBack(BIND_EVENT(Application::OnEvent));
	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		if (event.IsInCategory(EventCategory::EventCategoryApplication))
		{
			ECHO_CORE_TRACE(event.ToString());
		}

		m_bRunning = true;
		while (m_bRunning)
		{
			//更新主窗口
			m_MainWindow->OnUpdate();
		}

		if (event.IsInCategory(EventCategory::EventCategoryInput))
		{
			ECHO_CLIENT_TRACE(event.ToString());
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));	//控制窗口关闭
	}

	bool Application::OnWindowClose(WindowCloseEvent& closeEvent)
	{
		m_bRunning = false;
		return true;
	}

}
