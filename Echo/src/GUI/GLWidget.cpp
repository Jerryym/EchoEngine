#include "echopch.h"
#include <glad/glad.h>
#include "GLWidget.h"
#include <Nest.h>

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
		setFocusPolicy(Qt::StrongFocus);
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

#pragma region Input Events
	void GLWidget::keyPressEvent(QKeyEvent* event)
	{
		ECHO_CLIENT_INFO("keyPressEvent: {0}", event->text().toStdString());
	}

	void GLWidget::keyReleaseEvent(QKeyEvent* event)
	{
		ECHO_CLIENT_INFO("keyReleaseEvent: {0}", event->text().toStdString());
	}

	void GLWidget::mousePressEvent(QMouseEvent* event)
	{
		ECHO_CLIENT_INFO("mousePressEvent: {0}", event->button());
	}

	void GLWidget::mouseReleaseEvent(QMouseEvent* event)
	{
		ECHO_CLIENT_INFO("mouseReleaseEvent: {0}", event->button());
	}

	void GLWidget::mouseMoveEvent(QMouseEvent* event)
	{
		ECHO_CLIENT_INFO("mouseMoveEvent: ({0}, {1})", event->pos().x(), event->pos().y());
	}

	void GLWidget::wheelEvent(QWheelEvent* event)
	{
		ECHO_CLIENT_INFO("wheelEvent: {0}", event->button());
	}
#pragma endregion

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

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);  //设置 offscreen context 的标志位, 且GLFW的窗口会自动隐藏
		m_pGLFWwindow = glfwCreateWindow(nWidth, nHeight, strTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_pGLFWwindow);
		int status = gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
		ECHO_CORE_ASSERT(status, "Failed to initiazlize Glad!");
		SetVSync(true);	//设置垂直同步
	}

}
