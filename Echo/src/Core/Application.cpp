#include "echopch.h"
#include "Application.h"

#include <glad/glad.h>

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
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//遍历应用程序层栈，更新各层
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
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

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));	//控制窗口关闭

		//遍历应用程序层栈，处理各层事件
		for (Layer* layer : m_LayerStack)
		{
			layer->OnEvent(event);
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

}
