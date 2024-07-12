#include "echopch.h"
#include "Application.h"

namespace Echo {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
	}

	void Application::Run()
	{
	}

}
