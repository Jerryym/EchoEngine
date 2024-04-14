#include "echopch.h"
#include <glad/glad.h>
#include "GLWidget.h"
#include <QDateTime>

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		NEST_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLWidget::GLWidget(const std::string& strTitle, int nWidth, int nHeight, QWidget* parent)
		: QOpenGLWidget(parent)
	{
		//创建定时器，每隔16毫秒（大约60帧每秒）触发更新
		m_pTimer = new QTimer(this);
		connect(m_pTimer, &QTimer::timeout, this, QOverload<>::of(&GLWidget::update));
		m_pTimer->start(16);

		InitializeGLWidget(strTitle, nWidth, nHeight);
		setFocusPolicy(Qt::StrongFocus);
		setMouseTracking(true);
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
		glViewport(0, 0, width(), height());
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		//创建顶点缓冲对象
		float vertices[] = {
			-0.25f, -0.25f, 0.0f,
			0.0f,   0.25f, 0.0f,
			0.25f,  -0.25f, 0.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		//设置顶点属性指针
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//创建索引缓冲对象
		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		//创建着色器
		std::string vertexShader = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 offset;
			
			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0) + offset;
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			};
		)";
		m_Shader.reset(new Shader(vertexShader, fragmentShader));
	}

	void GLWidget::resizeGL(int w, int h)
	{
		glViewport(0, 0, w, h);
	}

	void GLWidget::paintGL()
	{
		render();
		m_Shader->Bind();
		m_pContext->SwapBuffers();
	}

#pragma region Input Events
	void GLWidget::keyPressEvent(QKeyEvent* event)
	{
		NEST_CLIENT_INFO("keyPressEvent: {0}", event->text().toStdString());
	}

	void GLWidget::keyReleaseEvent(QKeyEvent* event)
	{
		NEST_CLIENT_INFO("keyReleaseEvent: {0}", event->text().toStdString());
	}

	void GLWidget::mousePressEvent(QMouseEvent* event)
	{
		NEST_CLIENT_INFO("mousePressEvent: {0}", event->button());
	}

	void GLWidget::mouseReleaseEvent(QMouseEvent* event)
	{
		NEST_CLIENT_INFO("mouseReleaseEvent: {0}", event->button());
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

		//初始化当前上下文
		m_pContext = new OpenGLContext(m_pGLFWwindow);
		m_pContext->Init();
		
		//设置垂直同步
		SetVSync(true);	
	}

	void GLWidget::render()
	{
		float attrib[] = { 
			sin(QDateTime::currentSecsSinceEpoch()) * 0.5f,
			cos(QDateTime::currentSecsSinceEpoch()) * 0.6f,
			0.0f,
			0.0f
		};

		//更新offset值
		glVertexAttrib4fv(1, attrib);

		//绘制三角形
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

}
