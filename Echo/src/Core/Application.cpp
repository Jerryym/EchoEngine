#include "echopch.h"
#include "Application.h"

namespace Echo {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& sAppName)
	{
		ECHO_CORE_ASSERT(s_Instance != nullptr, "Application already exists!");
		s_Instance = this;
	}

	void Application::Run()
	{
		m_bRunning = true;
	}

	void Application::Close()
	{
		m_bRunning = false;
	}

}
