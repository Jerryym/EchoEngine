#pragma once
#include "Core.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Echo {

	/// @brief OpenGL渲染上下文
	class ECHO_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle, bool bSync = true);
		virtual ~OpenGLContext() {}

	public:
		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void Destroy() override;

	private:
		/// @brief 关联的GLFW窗口句柄
		GLFWwindow* m_pWindowHandle;
	};

}
