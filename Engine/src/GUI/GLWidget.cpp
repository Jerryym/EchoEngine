#include "echopch.h"
#include "GLWidget.h"

#include <Nest.h>
#include <NestUI.h>

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ECHO_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLWidget::GLWidget(const std::string& strTitle, int nWidth, int nHeight, QWidget* parent)
		: QOpenGLWidget(parent)
	{
		InitializeGLWidget(strTitle, nWidth, nHeight);
	}

	GLWidget::~GLWidget()
	{
		ShutDown();
	}

	void GLWidget::SetVSync(bool enabled)
	{
		if (enabled == true)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_bVSync = enabled;
	}

	void GLWidget::ShutDown()
	{
		glfwDestroyWindow(m_pGLFWwindow);
	}

	void GLWidget::initializeGL()
	{
	}

	void GLWidget::resizeGL(int w, int h)
	{
	}

	void GLWidget::paintGL()
	{
	}

	void GLWidget::InitializeGLWidget(const std::string& strTitle, int nWidth, int nHeight)
	{
		if (!s_bGLFWInitialiazed)
		{
			// glfwTerminate on system shutdown
			int success = glfwInit();
			NEST_CORE_ASSERT(success, "Could not intialiaze GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_bGLFWInitialiazed = true;
		}

		m_pGLFWwindow = glfwCreateWindow(nWidth, nHeight, strTitle.c_str(), nullptr, nullptr);
		SetVSync(true);	//设置垂直同步

		//隐藏 GLFW 窗口
		glfwHideWindow(m_pGLFWwindow);
	}

}
