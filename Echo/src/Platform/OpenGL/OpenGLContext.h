#pragma once
#include "Echo/Renderer/GraphicContext.h"

struct GLFWwindow;

namespace Echo {

	/// @brief OpenGL渲染上下文
	class OpenGLContext : public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

	public:
		// 通过 GraphicContext 继承
		void Init() override;

		void SwapBuffers() override;

	private:
		/// @brief 关联的GLFW窗口句柄
		GLFWwindow* m_pWindowHandle;
	};

}


