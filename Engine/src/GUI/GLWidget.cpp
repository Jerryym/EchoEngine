#include "enginepch.h"
#include "GLWidget.h"

#include <Nest.h>
#include <NestUI.h>

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ECHOENGINE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLWidget::GLWidget(QWidget* parent)
		: QOpenGLWidget(parent)
	{
		InitializeGLFW();
	}

	GLWidget::~GLWidget()
	{
		glfwDestroyWindow(m_pGLFWwindow);
	}

	void GLWidget::SetVSync(bool enabled)
	{
		if (enabled == true)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_bVSync = enabled;
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

	void GLWidget::InitializeGLFW()
	{
		auto mainWindow = dynamic_cast<NestUI::MainWindow*>(Nest::Application::GetApplication().GetMainWindow());
		NEST_CORE_ASSERT(mainWindow == nullptr, "MainWindow is Null!");
		int nWidth = mainWindow->GetWidth();
		int nHeight = mainWindow->GetHeigth();
		std::string sTitle = mainWindow->windowTitle().toStdString();

		if (!s_bGLFWInitialiazed)
		{
			// glfwTerminate on system shutdown
			int success = glfwInit();
			NEST_CORE_ASSERT(success, "Could not intialiaze GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_bGLFWInitialiazed = true;
		}
		m_pGLFWwindow = glfwCreateWindow((int)nWidth, (int)nHeight, sTitle.c_str(), nullptr, nullptr);
		SetVSync(true);	//设置垂直同步
	}

}
