#include "echopch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Echo {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle, bool bSync)
		: m_pWindowHandle(windowHandle)
	{
		ECHO_CORE_ASSERT(windowHandle, "Window handle is null!");
		//设置垂直同步
		if (bSync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}

	void OpenGLContext::Init()
	{
		//设置当前窗口上下文
		glfwMakeContextCurrent(m_pWindowHandle);
		//初始化GLAD
		int iStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ECHO_CORE_ASSERT(iStatus, "Failed to initiazlize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_pWindowHandle);
	}

	void OpenGLContext::Destroy()
	{
		glfwDestroyWindow(m_pWindowHandle);
	}

}
