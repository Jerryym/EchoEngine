#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Echo/Events/ApplicationEvent.hpp"
#include "Window.h"

namespace Echo {

	class ECHO_API Application
	{
	public:
		Application();
		virtual ~Application();

		/// @brief 当前事件
		/// @param event 
		void OnEvent(Event& event);

		/// @brief 运行
		void Run();

	private:
		/// @brief 关闭窗口
		/// @param closeEvent 窗口关闭事件
		/// @return true
		bool OnWindowClose(WindowCloseEvent& closeEvent);

		std::unique_ptr<Window> m_Window;	//应用显示窗口
		bool m_bRunning = true;				//运行状态的控制
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


