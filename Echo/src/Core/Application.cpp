#include "echopch.h"
#include "Application.h"

#include "Renderer/Renderer.h"

#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace Echo {

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& sAppName)
	{
		ECHO_CORE_ASSERT(s_Instance != nullptr, "Application already exists!");
		s_Instance = this;

		//创建主窗口
		m_MainWindow = MainWindow::CreateMainWindow(sWindowProp(sAppName));
		m_MainWindow->SetEventCallBack(BIND_EVENT(Application::OnEvent));
	}

	void Application::Run()
	{
		m_bRunning = true;
		while (m_bRunning)
		{
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_rLastFrameTime;
			m_rLastFrameTime = time;

			if (!m_bMinimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			}

			for (Layer* layer : m_LayerStack)
			{
				layer->OnRenderUI();
			}

			//更新主窗口
			m_MainWindow->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_bRunning = false;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));	//控制窗口关闭
		
		//遍历应用程序层栈，处理各层事件
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled() == true)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& closeEvent)
	{
		m_bRunning = false;
		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent& resizeEvent)
	{
		if (resizeEvent.getWidth() == 0 || resizeEvent.getHeight() == 0)
		{
			m_bMinimized = true;
			return false;
		}
		m_bMinimized = false;
		Renderer::WindowResize(resizeEvent.getWidth(), resizeEvent.getHeight());
		return false;
	}

}
