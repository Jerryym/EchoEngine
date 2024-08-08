#include "echopch.h"
#include "Application.h"

#include "Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Echo {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ECHO_CORE_ASSERT(s_Instance != nullptr, "Application already exists!");
		s_Instance = this;

		//创建主窗口
		m_MainWindow = std::unique_ptr<MainWindow>(MainWindow::CreateMainWindow());
		m_MainWindow->SetEventCallBack(BIND_EVENT(Application::OnEvent));

		//创建ImGUI图层
		m_ImGuiLayer = new ImGUILayer;
		PushOverLayer(m_ImGuiLayer);
	}

	void Application::Run()
	{
		m_bRunning = true;
		while (m_bRunning)
		{
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (m_bMinimized != true)
			{
				//遍历应用程序层栈，更新各层
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			}

			//渲染ImGUI
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnRenderUI();
			}
			m_ImGuiLayer->End();

			//更新主窗口
			m_MainWindow->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));	//窗口关闭
		dispatcher.Dispatcher<WindowResizeEvent>(BIND_EVENT(Application::OnWindowResized));	//窗口大小修改

		//遍历应用程序层栈，处理各层事件
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled() == true)
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
