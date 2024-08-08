#pragma once
#include "Core.h"

#include "GUI/MainWindow.h"
#include "Core/Events/ApplicationEvent.hpp"

#include "Core/Layer.h"
#include "Core/LayerStack.h"

#include "GUI/ImGUI/ImGUILayer.h"

namespace Echo {

	/// @brief 应用程序类：用于管理应用程序运行状态和运行中的资源
	class Application
	{
	public:
		Application();
		virtual ~Application() {}

	public:
		/// @brief 启动应用程序
		void Run();

		/// @brief 获取当前应用程序
		/// @return 当前运行的应用程序指针
		inline static Application& GetApplication() { return *s_Instance; }

		/// @brief 获取当前活动主窗口
		/// @return 当前活动主窗口指针
		inline MainWindow& GetMainWindow() { return *m_MainWindow; }

		/// @brief 当前事件
		/// @param event 
		void OnEvent(Event& event);

		/// @brief 添加层
		/// @param layer 
		void PushLayer(Layer* layer);

		/// @brief 添加层
		/// @param layer 
		void PushOverLayer(Layer* layer);

	private:
		/// @brief 关闭窗口
		/// @param closeEvent 窗口关闭事件
		/// @return true
		bool OnWindowClose(WindowCloseEvent& closeEvent);
		/// @brief 修改窗口大小
		/// @param resizeEvent 
		/// @return 
		bool OnWindowResized(WindowResizeEvent& resizeEvent);

	private:
		/// @brief 应用程序单例（程序运行时，当且只能一个应用程序存在）
		static Application* s_Instance;
		/// @brief 运行状态
		bool m_bRunning = false;
		/// @brief 最小化
		bool m_bMinimized = false;
		/// @brief 应用程序层栈
		LayerStack m_LayerStack;
		/// @brief 最后一帧的时间
		float m_LastFrameTime = 0.0f;

		/// @brief 应用程序主窗口
		std::unique_ptr<MainWindow> m_MainWindow;
		/// @brief ImGUI图层
		ImGUILayer* m_ImGuiLayer = nullptr;
	};

	
	// defined in Client 
	Application* CreateApplication();

}
