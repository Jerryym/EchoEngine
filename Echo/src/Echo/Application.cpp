#include "echopch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Echo {

#define BIND_EVENT(x)	 std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		// 输出当前所属事件日志
		ECHO_CLIENT_INFO("{0}", event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));	//控制窗口关闭
	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		
		if (event.IsInCategory(EventCategoryApplication))
		{
			ECHO_CORE_TRACE(event);
		}

		while (m_bRunning)
		{
			glClearColor(0.3f, 0.3f, 0.2f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}

		if (event.IsInCategory(EventCategoryInput))
		{
			ECHO_CLIENT_TRACE(event);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& closeEvent)
	{
		m_bRunning = false;
		return true;
	}

}