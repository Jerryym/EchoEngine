#pragma once
#include "Echo/Window.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace Echo {

	class Windows_Window :	public Window
	{
	public:
		Windows_Window(const sWindowProps& prop);
		virtual ~Windows_Window();

		virtual void OnUpdate() override;

		unsigned int GetWidth() const override { return m_sData.m_nWidth; }
		unsigned int GetHeight() const override { return m_sData.m_nHeight; }

		virtual void SetEventCallBack(const EventCallBackFun& callback) override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_pWindow; }

	private:
		/// @brief 初始化
		virtual void Initialize(const sWindowProps& props);

		/// @brief 窗口关闭
		virtual void ShutDown();

	private:
		GLFWwindow* m_pWindow;
		GraphicsContext* m_pContext;	//渲染上下文
		
		/// @brief 窗口数据
		typedef struct sWindowData
		{
			unsigned int m_nWidth = 0;
			unsigned int m_nHeight = 0;
			std::string m_strTitle;
			bool m_bVSync = true;	//是否开启垂直同步
			EventCallBackFun m_Eventcallback;	//事件回调函数
		}sWindowData;

		sWindowData m_sData;

	};

}


