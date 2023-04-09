#pragma once
#include "Echo/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Echo {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext();
		OpenGLContext(GLFWwindow* windowhandle);
		~OpenGLContext() {}

		virtual void Init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* m_pWindowhandle;
	};

}


