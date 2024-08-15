#include "echopch.h"
#include "MainWindow_Windows.h"

#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Events/KeyEvent.hpp"
#include "Core/Events/MouseEvent.hpp"

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ECHO_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	///////////////////////////////////////////////////////////////////
	// MainWindow_Windows
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
		m_pContext->SwapBuffers();
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

	void MainWindow_Windows::SetEventCallBack(const EventCallBackFun& callback)
	{
		m_sData.m_Eventcallback = callback;
	}

	void MainWindow_Windows::Initialize(const sWindowProp& props)
	{
		m_sData.m_nWidth = props.m_iWidth;
		m_sData.m_nHeight = props.m_iHeight;
		m_sData.m_strTitle = props.m_sTitle;

		ECHO_CORE_INFO("Create MainWindow {0} ({1}, {2})", props.m_sTitle, props.m_iWidth, props.m_iHeight);

		if (!s_bGLFWInitialiazed)
		{
			// glfwTerminate on system shutdown
			int success = glfwInit();
			ECHO_CORE_ASSERT(success, "Could not intialiaz GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_bGLFWInitialiazed = true;
		}
		m_pGLFWWindow = glfwCreateWindow((int)props.m_iWidth, (int)props.m_iHeight, props.m_sTitle.c_str(), nullptr, nullptr);
		
		//初始化上下文
		m_pContext = new OpenGLContext(m_pGLFWWindow);
		m_pContext->Init();
		glfwSetWindowUserPointer(m_pGLFWWindow, &m_sData);
		SetVSync(true);	//设置垂直同步

		//////////////////////////////////////////////////////////////
		// 设置GLFW事件回调 ///////////////////////////////////////////
		//////////////////////////////////////////////////////////////
		//glfwSetWindowSizeCallback - 重置窗口大小
		glfwSetWindowSizeCallback(m_pGLFWWindow, [](GLFWwindow* window, int width, int height)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);
				sData.m_nWidth = width;
				sData.m_nHeight = height;
				WindowResizeEvent resizeEvent(width, height);
				sData.m_Eventcallback(resizeEvent);
			});

		//glfwSetWindowCloseCallback - 关闭窗口
		glfwSetWindowCloseCallback(m_pGLFWWindow, [](GLFWwindow* window)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent closeEvent;
				sData.m_Eventcallback(closeEvent);
			});

		//glfwSetKeyCallback - 键盘操作
		glfwSetKeyCallback(m_pGLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);
				switch (action)//action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent keyEvent(key);
						sData.m_Eventcallback(keyEvent);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent keyEvent(key);
						sData.m_Eventcallback(keyEvent);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent keyEvent(key, true);
						sData.m_Eventcallback(keyEvent);
						break;
					}
				}
			});

		//glfwSetCharCallback - 键盘键入操作
		glfwSetCharCallback(m_pGLFWWindow, [](GLFWwindow* window, unsigned int codepoint)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(codepoint);
				sData.m_Eventcallback(event);
			});

		//glfwSetMouseButtonCallback - 鼠标按键操作
		glfwSetMouseButtonCallback(m_pGLFWWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);
				switch (action)//action One of `GLFW_PRESS` or `GLFW_RELEASE`
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent mouseEvent(button);
						sData.m_Eventcallback(mouseEvent);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent mouseEvent(button);
						sData.m_Eventcallback(mouseEvent);
						break;
					}
				}
			});

		//glfwSetScrollCallback - 滚轮滚动操作
		glfwSetScrollCallback(m_pGLFWWindow, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent mouseEvent((float)xoffset, (float)yoffset);
				sData.m_Eventcallback(mouseEvent);
			});

		//glfwSetCursorPosCallback - 当前鼠标位置
		glfwSetCursorPosCallback(m_pGLFWWindow, [](GLFWwindow* window, double xpos, double ypos)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent mouseEvent((float)xpos, (float)ypos);
				sData.m_Eventcallback(mouseEvent);
			});
	}

	void MainWindow_Windows::ShutDown()
	{
		//释放GLFW资源
		glfwDestroyWindow(m_pGLFWWindow);
	}

}
