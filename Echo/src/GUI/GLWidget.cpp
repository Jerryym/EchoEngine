#include "echopch.h"
#include <glad/glad.h>
#include "GLWidget.h"

namespace Echo {

	static bool s_bGLFWInitialiazed = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		NEST_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLWidget::GLWidget(const std::string& strTitle, int nWidth, int nHeight, QWidget* parent)
		: QOpenGLWidget(parent)
	{
		InitializeGLWidget(strTitle, nWidth, nHeight);
		setFocusPolicy(Qt::StrongFocus);
		setMouseTracking(true);

		//创建定时器，每隔16毫秒（大约60帧每秒）触发更新
		m_pTimer = new QTimer;
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
		glViewport(0, 0, width(), height());
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//创建顶点数组对象
		m_TriangleVA.reset(VertexArray::Create());
		float triangleVertices[] = {
			-0.25f, -0.25f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.25f, -0.25f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,   0.25f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		
		//创建顶点缓冲对象
		std::shared_ptr<VertexBuffer> TriangleVB;
		TriangleVB.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		BufferLayout triangleLayout = {
					{ ShaderDataType::Float3, "a_Position" },
					{ ShaderDataType::Float4, "a_Color" }
		};
		TriangleVB->SetLayout(triangleLayout);
		m_TriangleVA->AddVertexBuffer(TriangleVB);

		//创建索引缓冲对象
		std::shared_ptr<IndexBuffer> TriangleIB;
		uint32_t triangleIndices[3] = { 0,1,2 };
		TriangleIB.reset(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		m_TriangleVA->SetIndexBuffer(TriangleIB);

		//创建着色器
		std::string vertexShader = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(new Shader(vertexShader, fragmentShader));

		//background矩形
		m_SquareVA.reset(VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.5f, -0.75f, 0.0f,
			 0.5f, -0.75f, 0.0f,
			 0.5f,  0.75f, 0.0f,
			-0.5f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void GLWidget::resizeGL(int w, int h)
	{
		glViewport(0, 0, w, h);
	}

	void GLWidget::paintGL()
	{
		render();
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
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//绘制矩形
		m_BlueShader->Bind();
		m_SquareVA->Bind();
		glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

		//绘制三角形
		m_Shader->Bind();
		m_TriangleVA->Bind();
		glDrawElements(GL_TRIANGLES, m_TriangleVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

		//交换缓冲
		m_pContext->SwapBuffers();
	}

}
