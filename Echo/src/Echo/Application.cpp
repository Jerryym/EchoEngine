#include "echopch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Echo {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ECHO_CORE_ASSERT(s_Instance != nullptr, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));	//���ƴ��ڹر�

		//������ϵ��¼�
		for (Layer* layer : m_LayerStack)
		{
			layer->OnEvent(event);
		}
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

			// ������ջ��ʵ�ָ������
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}

		if (event.IsInCategory(EventCategoryInput))
		{
			ECHO_CLIENT_TRACE(event);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& closeEvent)
	{
		m_bRunning = false;
		return true;
	}

}