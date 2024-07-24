#pragma once
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Echo {

	/// @brief OpenGL上下文
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual ~OpenGLContext() {}

	public:
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_pWindowHandle;
	};

}
