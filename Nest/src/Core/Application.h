#pragma once
#include "NestCore.h"
#include <QApplication>
#include <QMainWindow>
#include "LayerStack.h"

namespace Nest {

	/// @brief 应用程序类
	class NEST_API Application : public QApplication
	{
		Q_OBJECT
	public:
		Application(int& argc, char** argv);
		virtual ~Application() {}
	
	public:
		/// @brief 运行应用程序
		void Run();
		/// @brief 获取应用程序运行状态
		/// @return 
		inline bool IsRun() { return m_bRunning; }
		/// @brief 设置主窗口
		/// @param pMainWindow 
		void SetMainWindow(QMainWindow* pMainWindow);
		/// @brief 获取主窗口
		/// @return 当前活动窗口指针
		inline QMainWindow* GetMainWindow() { return m_Window.get(); }
		/// @brief 获取当前应用程序
		/// @return 
		inline static Application& GetApplication() { return *s_Instance; }

	public:
		/// @brief 从层栈的第一个元素添加一个层级
		/// @param layer 
		void PushLayer(Layer* layer);
		/// @brief 添加一个层到栈
		/// @param layer 
		void PushOverlay(Layer* layer);
		/// @brief 初始化Layer
		virtual void InitLayer() {}
		/// @brief 获取层栈
		/// @return 
		static LayerStack& GetLayerStack() { return s_Instance->m_LayerStack; }

	private:
		/// @brief 应用程序单例: 程序运行时，当且只能一个应用程序存在
		static Application* s_Instance;
		/// @brief 运行状态的控制
		bool m_bRunning = false;
		/// @brief 应用程序主窗口
		std::unique_ptr<QMainWindow> m_Window;
		/// @brief 层栈
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication(int argc, char** argv);
}

