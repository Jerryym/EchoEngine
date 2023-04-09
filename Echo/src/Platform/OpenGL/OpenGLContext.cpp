#include "echopch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Echo {

	OpenGLContext::OpenGLContext()
		:m_pWindowhandle(nullptr)
	{
	}

	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
		:m_pWindowhandle(windowhandle)
	{
		ECHO_CORE_ASSERT(windowhandle, "Window Handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_pWindowhandle);	//设置当前窗口上下文
		int status = gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
		ECHO_CORE_ASSERT(status, "Failed to initiazlize Glad!");

		ECHO_CORE_INFO("OpenGL Info: ");
		ECHO_CORE_INFO(" Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		ECHO_CORE_INFO(" Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		ECHO_CORE_INFO(" Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_pWindowhandle);
	}

}