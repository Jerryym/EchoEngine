#include "echopch.h"
#include "Windows_Window.h"

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	Window* Window::Create(const const sWindowProps& props)
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

			s_bGLFWInitialiazed = true;
		}

		m_pWindow = glfwCreateWindow((int)props.m_nWidth, (int)props.m_nHeight, props.m_strTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_pWindow);	//设置当前窗口上下文
		glfwSetWindowUserPointer(m_pWindow, &m_sData);
		SetVSync(true);	//设置垂直同步
	}

	void Windows_Window::ShutDown()
	{
		glfwDestroyWindow(m_pWindow);
	}

}