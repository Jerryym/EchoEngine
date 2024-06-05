#include "echopch.h"
#include "GLWidget.h"
#include "Core/Application.h"

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		NEST_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLWidget::GLWidget(const std::string& strTitle, int nWidth, int nHeight, QWidget* parent)
		: QOpenGLWidget(parent)
	{
		setFocus();
		InitializeGLWidget(strTitle, nWidth, nHeight);

		//创建定时器，每隔16毫秒（大约60帧每秒）触发更新
		m_pTimer = new QTimer(this);
		m_pTimer->setInterval(16.67);
		connect(m_pTimer, &QTimer::timeout, this, QOverload<>::of(&GLWidget::update));
		m_pTimer->start();
	}

	GLWidget::~GLWidget()
	{
		delete m_pTimer;
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
		//初始化OpenGL
		m_pContext->Init();
		//设置垂直同步
		SetVSync(m_bVSync);
	}

	void GLWidget::resizeGL(int w, int h)
	{
		glViewport(0, 0, w, h);
	}

	void GLWidget::paintGL()
	{
		//遍历层栈，实现各层更新
		m_layerStack = Nest::Application::GetLayerStack();
		for (auto layer : m_layerStack)
		{
			if (layer->IsValid() == true)
			{
				layer->OnUpdate();
			}
		}
		//交换缓冲
		m_pContext->SwapBuffers();
	}

#pragma region Input Events
	void GLWidget::keyPressEvent(QKeyEvent* event)
	{
		NEST_CLIENT_INFO("keyPressEvent: {0}", event->text().toStdString());
		for (auto layer : m_layerStack)
		{
			if (layer->IsValid() == true)
			{
				layer->OnKeyPressedEvent(event->key());
			}
		}
		update();
	}

	void GLWidget::mousePressEvent(QMouseEvent* event)
	{
		//NEST_CLIENT_INFO("mousePressEvent: {0}", event->button());
	}

	void GLWidget::mouseReleaseEvent(QMouseEvent* event)
	{
		//NEST_CLIENT_INFO("mouseReleaseEvent: {0}", event->button());
	}

	void GLWidget::mouseMoveEvent(QMouseEvent* event)
	{
		//NEST_CLIENT_INFO("mouseMoveEvent: ({0}, {1})", event->pos().x(), event->pos().y());
	}

	void GLWidget::wheelEvent(QWheelEvent* event)
	{
		NEST_CLIENT_INFO("wheelEvent: {0}", event->button());
	}
#pragma endregion

	void GLWidget::InitializeGLWidget(const std::string& strTitle, int nWidth, int nHeight)
	{
		if (!s_bGLFWInitialiazed)
		{
			// glfwTerminate on system shutdown
			int success = glfwInit();
			ECHO_CORE_ASSERT(success, "Could not intialiaze GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_bGLFWInitialiazed = true;
		}
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);  //设置 offscreen context 的标志位, 且GLFW的窗口会自动隐藏
		m_pGLFWwindow = glfwCreateWindow(nWidth, nHeight, strTitle.c_str(), nullptr, nullptr);

		//初始化OpenGL上下文
		m_pContext = new OpenGLContext(m_pGLFWwindow);
	}

}
