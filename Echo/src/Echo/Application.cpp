#include "echopch.h"
#include "Application.h"

namespace Echo {

	Application* Application::s_Instance = nullptr;

	Application::Application(int& argc, char** argv)
		: QApplication(argc, argv)
	{
		s_Instance = this;
	}

	void Application::SetMainWindow(QMainWindow* mainWindow)
	{
		s_Instance->m_Window.reset(mainWindow);
	}

}
