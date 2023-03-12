#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Echo/Events/ApplicationEvent.hpp"
#include "Window.h"
#include "LayerStack.h"

namespace Echo {

	class ECHO_API Application
	{
	public:
		Application();
		virtual ~Application();

		/// @brief ��ǰ�¼�
		/// @param event 
		void OnEvent(Event& event);

		/// @brief ����Ӧ�ó���
		void Run();

		/// @brief �Ӳ�ջ�ĵ�һ��Ԫ�����һ���㼶
		/// @param layer 
		void PushLayer(Layer* layer);

		/// @brief ���һ���㵽ջ
		/// @param layer 
		void PushOverlay(Layer* layer);

		/// @brief ��ȡ��ǰӦ�ó���
		/// @return ��ǰӦ�ó���ָ��
		inline static Application& GetApplication() { return *s_Instance; }
		
		/// @brief ��ȡ��ǰ�����
		/// @return ��ǰ�����ָ��
		inline Window& GetWindow() { return *m_Window; }

	private:
		/// @brief �رմ���
		/// @param closeEvent ���ڹر��¼�
		/// @return true
		bool OnWindowClose(WindowCloseEvent& closeEvent);

		std::unique_ptr<Window> m_Window;	//Ӧ����ʾ����
		bool m_bRunning = true;				//����״̬�Ŀ���
		LayerStack m_LayerStack;			//��ջ

		//Ӧ�ó�����ָ�루��������ʱ������ֻ��һ��Ӧ�ó�����ڣ�
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


