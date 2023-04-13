#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Echo/Events/ApplicationEvent.hpp"
#include "Window.h"
#include "LayerStack.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"

namespace Echo {

	class ECHO_API Application
	{
	public:
		Application();
		virtual ~Application();

		/// @brief 当前事件
		/// @param event 
		void OnEvent(Event& event);

		/// @brief 运行应用程序
		void Run();

		/// @brief 从层栈的第一个元素添加一个层级
		/// @param layer 
		void PushLayer(Layer* layer);

		/// @brief 添加一个层到栈
		/// @param layer 
		void PushOverlay(Layer* layer);

		/// @brief 获取当前应用程序
		/// @return 当前应用程序指针
		inline static Application& GetApplication() { return *s_Instance; }
		
		/// @brief 获取当前活动窗口
		/// @return 当前活动窗口指针
		inline Window& GetWindow() { return *m_Window; }

	private:
		/// @brief 关闭窗口
		/// @param closeEvent 窗口关闭事件
		/// @return true
		bool OnWindowClose(WindowCloseEvent& closeEvent);

		std::unique_ptr<Window> m_Window;	//应用显示窗口
		ImGuiLayer* m_pImGuiLayer;			//ImGui UI层
		bool m_bRunning = true;				//运行状态的控制
		LayerStack m_LayerStack;			//层栈

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;	//着色器

		//应用程序单例指针（程序运行时，当且只能一个应用程序存在）
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


