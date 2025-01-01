#pragma once
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Echo {

	/// @brief OpenGL渲染上下文
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(uint32_t nWidth, uint32_t nHeight, const std::string& sTitle, bool bShowWindow = true);
		virtual ~OpenGLContext() {}

	public:
		virtual void Init() override;
		virtual void MakeCurrent() override;
		virtual void SwapBuffers() override;
		virtual void Destroy() override;
		virtual void* GetWindowHandle() override;

	private:
		void Create(uint32_t nWidth, uint32_t nHeight, const std::string& sTitle, bool bShowWindow);

	private:
		/// @brief 关联的GLFW窗口句柄
		GLFWwindow* m_pWindowHandle;
	};

}
