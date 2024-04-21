#include "echopch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Echo {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_pWindowHandle(windowHandle)
	{
		ECHO_CORE_ASSERT(windowhandle, "Window Handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_pWindowHandle);
		int status = gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
		ECHO_CORE_ASSERT(status, "Failed to initiazlize Glad!");

		NEST_CORE_INFO("OpenGL Info: Vendor: {0} | Renderer: {1} | Version: {2}", 
			reinterpret_cast<const char*>(glGetString(GL_VENDOR)), reinterpret_cast<const char*>(glGetString(GL_RENDERER)), reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_pWindowHandle);
	}
}
