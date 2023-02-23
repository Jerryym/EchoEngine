#include "echopch.h"
#include "Windows_Window.h"

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ECHO_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const sWindowProps& props)
	{
		return new Windows_Window(props);
	}

	Windows_Window::Windows_Window(const sWindowProps& prop)
	{
		Initialize(prop);
	}

	Windows_Window::~Windows_Window()
	{
		ShutDown();
	}

	void Windows_Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_pWindow);
	}

	void Windows_Window::SetEventCallBack(const EventCallBackFun& callback)
	{
		m_sData.m_Eventcallback = callback;
	}

	/// @brief 设置交换间隔时间, 即垂直同步
	/// @param enabled 
	void Windows_Window::SetVSync(bool enabled)
	{
		if (enabled)		
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_sData.m_bVSync = enabled;
	}

	bool Windows_Window::IsVSync() const
	{
		return m_sData.m_bVSync;
	}

	void Windows_Window::Initialize(const sWindowProps& props)
	{
		m_sData.m_nWidth = props.m_nWidth;
		m_sData.m_nHeight = props.m_nHeight;
		m_sData.m_strTitle = props.m_strTitle;

		ECHO_CORE_INFO("Create window {0} ({1}, {2})", props.m_nWidth, props.m_nHeight, props.m_strTitle);

		if (!s_bGLFWInitialiazed)
		{
			// glfwTerminate on system shutdown
			int success = glfwInit();
			ECHO_CORE_ASSERT(success, "Could not intialiaz GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_bGLFWInitialiazed = true;
		}

		m_pWindow = glfwCreateWindow((int)props.m_nWidth, (int)props.m_nHeight, props.m_strTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_pWindow);	//设置当前窗口上下文
		glfwSetWindowUserPointer(m_pWindow, &m_sData);
		SetVSync(true);	//设置垂直同步

		/*
		* 设置GLFW 窗口事件回调
		* glfwSetWindowSizeCallback - 重置窗口大小
		* glfwSetWindowCloseCallback - 关闭窗口
		* glfwSetKeyCallback - 键盘操作
		* glfwSetMouseButtonCallback - 鼠标按键操作
		* glfwSetScrollCallback - 滚轮滚动操作
		* glfwSetCursorPosCallback - 当前鼠标位置
		*/
		glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* window, int width, int height)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);

				sData.m_nWidth = width;
				sData.m_nHeight = height;

				WindowResizeEvent resizeEvent(width, height);
				sData.m_Eventcallback(resizeEvent);
			});

		glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* window)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent closeEvent;
				sData.m_Eventcallback(closeEvent);
			});

		glfwSetKeyCallback(m_pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);

				switch (action)
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

		glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);

				switch (action)
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

		glfwSetScrollCallback(m_pWindow, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent mouseEvent((float)xoffset, (float)yoffset);
				sData.m_Eventcallback(mouseEvent);
			});

		glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* window, double xpos, double ypos)
			{
				sWindowData& sData = *(sWindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent mouseEvent((float)xpos, (float)ypos);
				sData.m_Eventcallback(mouseEvent);
			});
	}

	void Windows_Window::ShutDown()
	{
		glfwDestroyWindow(m_pWindow);
	}

}