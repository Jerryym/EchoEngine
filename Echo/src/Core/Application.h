#pragma once
#include "Core.h"

namespace Echo {

	/// @brief 应用程序类
	class ECHO_API Application
	{
	public:
		Application(const std::string& sAppName = "Echo Engine");
		virtual ~Application() = default;

	public:
		/// @brief 获取当前应用程序
		/// @return 
		inline static Application& GetApplication() { return *s_Instance; }

		/// @brief 启动应用程序
		void Run();
		/// @brief 关闭应用程序
		void Close();

	private:
		/// @brief 应用程序单例(程序运行时，当且只能有一个应用程序存在)
		static Application* s_Instance;
		/// @brief 运行状态
		bool m_bRunning = false;

	};

	// defined in Client
	Application* CreateApplication();

}
