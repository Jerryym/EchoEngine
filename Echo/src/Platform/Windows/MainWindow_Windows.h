#pragma once
#include "GUI/MainWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include <GLFW/glfw3.h>

namespace Echo {

	class MainWindow_Windows : public MainWindow
	{
	public:
		MainWindow_Windows(const sWindowProp& sProp);
		virtual ~MainWindow_Windows();

	public:
		virtual void OnUpdate() override;

		virtual unsigned int GetWidth() const override { return m_sData.m_nWidth; }
		virtual unsigned int GetHeight() const override { return m_sData.m_nHeight; }
		virtual const std::string& GetTitle() const override { return m_sData.m_strTitle; }

		virtual void SetVSync(bool bEnable) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_pGLFWWindow; }

		virtual void SetEventCallBack(const EventCallBackFun& callback) override;

	private:
		/// @brief 初始化窗口
		virtual void Initialize(const sWindowProp& props);
		/// @brief 窗口关闭
		virtual void ShutDown();

	private:
		/// @brief 窗口数据
		typedef struct sWindowData
		{
			unsigned int m_nWidth = 0;
			unsigned int m_nHeight = 0;
			std::string m_strTitle;
			bool m_bVSync = true;				//是否开启垂直同步
			EventCallBackFun m_Eventcallback;	//事件回调函数
		}sWindowData;

		sWindowData m_sData;
		GLFWwindow* m_pGLFWWindow;
		/// @brief 渲染上下文
		GraphicsContext* m_pContext;
	};

}

