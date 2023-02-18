#include "echopch.h"
#include "Application.h"

#include "Echo/Events/ApplicationEvent.hpp"

#include <GLFW/glfw3.h>

namespace Echo {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		
		if (event.IsInCategory(EventCategoryApplication))
		{
			ECHO_CORE_TRACE(event);
		}

		if (event.IsInCategory(EventCategoryInput))
		{
			ECHO_CORE_TRACE(event);
		}

		while (m_bRunning)
		{
			glClearColor(0.5f, 0.3f, 0.2f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}