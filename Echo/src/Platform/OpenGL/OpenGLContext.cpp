#include "echopch.h"
#include "OpenGLContext.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glad/glad.h>

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	OpenGLContext::OpenGLContext(uint32_t nWidth, uint32_t nHeight, const std::string& sTitle, bool bShowWindow)
	{
		Create(nWidth, nHeight, sTitle, bShowWindow)
		ECHO_CORE_ASSERT(m_pWindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		//设置当前窗口上下文
		glfwMakeContextCurrent(m_pWindowHandle);
		//初始化GLAD
		int iStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ECHO_CORE_ASSERT(iStatus != 1, "Failed to initiazlize Glad!");
		//设置垂直同步
		glfwSwapInterval(1);
	}

	void OpenGLContext::MakeCurrent()
	{
		if (m_pWindowHandle) 
		{
			glfwMakeContextCurrent(m_pWindowHandle);
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_pWindowHandle);
	}

	void OpenGLContext::Destroy()
	{
		glfwDestroyWindow(m_pWindowHandle);
	}

	void* OpenGLContext::GetWindowHandle()
	{
		#if defined(_WIN32)// Windows: Use glfwGetWin32Window
			return glfwGetWin32Window(m_pWindowHandle);
		#else
			ECHO_CORE_ASSERT(false, "Unsupported platform for embedding GLFW window.");
			return nullptr;
		#endif
	}

	void OpenGLContext::Create(uint32_t nWidth, uint32_t nHeight, const std::string& sTitle, bool bShowWindow)
	{
		//创建GLFW窗口
		if (!s_bGLFWInitialiazed)
		{
			// glfwTerminate on system shutdown
			int success = glfwInit();
			ECHO_CORE_ASSERT(success, "Could not intialiaz GLFW!");
			s_bGLFWInitialiazed = true;
		}
		glfwWindowHint(GLFW_VISIBLE, bShowWindow == true ? GLFW_TRUE : GLFW_FALSE);
		m_pWindowHandle = glfwCreateWindow((int)nWidth, (int)nHeight, "EchoEngine", nullptr, nullptr);
	}

}
