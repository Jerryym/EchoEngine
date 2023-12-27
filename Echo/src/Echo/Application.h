#pragma once

#include <QApplication>
#include <QMainWindow>

#include "Core.h"

namespace Echo {

	/// @brief 应用程序类
	class ECHO_API Application : public QApplication
	{
		Q_OBJECT
	public:
		Application(int& argc, char** argv);
		virtual ~Application() {}
	
	public:
		/// @brief 获取当前应用程序
		/// @return 
		inline static Application& GetApplication() { return *s_Instance; }

		/// @brief 设置主窗口
		/// @param mainWindow 
		static void SetMainWindow(QMainWindow* mainWindow);

		/// @brief 获取当前活动窗口
		/// @return 当前活动窗口指针
		inline QMainWindow& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<QMainWindow> m_Window;	//应用显示窗口
		bool m_bRunning = true;					//运行状态的控制
		
		/// @brief 应用程序单例: 程序运行时，当且只能一个应用程序存在
		static Application* s_Instance;
	};

}

