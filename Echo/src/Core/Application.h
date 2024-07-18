#pragma once
#include "GUI/MainWindow.h"

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

	private:
		/// @brief 应用程序单例（程序运行时，当且只能一个应用程序存在）
		static Application* s_Instance;
		/// @brief 运行状态
		bool m_bRunning = true;
		/// @brief 应用程序主窗口
		std::unique_ptr<MainWindow> m_MainWindow;
	};

	
	// defined in Client 
	Application* CreateApplication();

}
