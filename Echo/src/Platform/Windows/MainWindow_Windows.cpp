#include "echopch.h"
#include "MainWindow_Windows.h"

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ECHO_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	///////////////////////////////////////////////////////////////////
	// MainWindow_Windows
	MainWindow* MainWindow::CreateMainWindow(const sWindowProp& prop)
	{
		return new MainWindow_Windows(prop);
	}

	MainWindow_Windows::MainWindow_Windows(const sWindowProp& sProp)
	{
		Initialize(sProp);
	}

	MainWindow_Windows::~MainWindow_Windows()
	{
		ShutDown();
	}

	void MainWindow_Windows::OnUpdate()
	{
		// 检查是否有事件触发
		glfwPollEvents();
		// 交换缓冲区
		glfwSwapBuffers(m_pGLFWWindow);
	}

	void MainWindow_Windows::SetVSync(bool bEnable)
	{
		if (bEnable == true)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_sData.m_bVSync = bEnable;
	}

	bool MainWindow_Windows::IsVSync() const
	{
		return m_sData.m_bVSync;
	}

	void MainWindow_Windows::Initialize(const sWindowProp& props)
	{
		m_sData.m_nWidth = props.m_iWidth;
		m_sData.m_nHeight = props.m_iHeight;
		m_sData.m_strTitle = props.m_sTitle;

		ECHO_CORE_INFO("Create window {0} ({1}, {2})", props.m_sTitle, props.m_iWidth, props.m_iHeight);

		if (!s_bGLFWInitialiazed)
		{
			// glfwTerminate on system shutdown
			int success = glfwInit();
			ECHO_CORE_ASSERT(success, "Could not intialiaz GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_bGLFWInitialiazed = true;
		}
		m_pGLFWWindow = glfwCreateWindow((int)props.m_iWidth, (int)props.m_iHeight, props.m_sTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_pGLFWWindow);	//设置当前窗口上下文
		glfwSetWindowUserPointer(m_pGLFWWindow, &m_sData);
		SetVSync(true);	//设置垂直同步
	}

	void MainWindow_Windows::ShutDown()
	{
		//释放GLFW资源
		glfwDestroyWindow(m_pGLFWWindow);
	}

}
