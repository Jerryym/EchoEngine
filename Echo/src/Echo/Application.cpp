#include "Application.h"

#include "Echo/Events/ApplicationEvent.hpp"
#include "Echo/Log.h"

namespace Echo {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		ECHO_CLIENT_TRACE(event);

		while (true);
	}

}