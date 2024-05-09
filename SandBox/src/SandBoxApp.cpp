#include <Echo.h>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

class ExampleLayer : public Nest::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		//创建顶点数组对象
		m_TriangleVA.reset(Echo::VertexArray::Create());
		float triangleVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		//创建顶点缓冲对象
		m_TriangleVB.reset(Echo::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		Echo::BufferLayout triangleLayout = {
			{ Echo::ShaderDataType::Float3, "a_Position" },
			{ Echo::ShaderDataType::Float4, "a_Color" }
		};
		m_TriangleVB->SetLayout(triangleLayout);

		//创建索引缓冲对象
		uint32_t triangleIndices[3] = { 0,1,2 };
		m_TriangleIB.reset(Echo::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));

		//创建着色器
		std::string vertexShader = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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
		m_Shader.reset(new Echo::Shader(vertexShader, fragmentShader));

		//background矩形
		m_SquareVA.reset(Echo::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		
		m_SquareVB.reset(Echo::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_SquareVB->SetLayout({
			{ Echo::ShaderDataType::Float3, "a_Position" }
		});
		

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		m_SquareIB.reset(Echo::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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
		m_BlueShader.reset(new Echo::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	virtual void OnUpdate() override
	{
		Echo::RenderCommond::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
		Echo::RenderCommond::Clear(GL_COLOR_BUFFER_BIT);

		m_camera.SetPosition(m_CameraPosition);
		m_camera.SetRotation(m_CameraRotation);
		
		Echo::Renderer::BeginScene(m_camera);
		
		//绘制矩形
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		m_SquareVA->AddVertexBuffer(m_SquareVB);
		m_SquareVA->SetIndexBuffer(m_SquareIB);
		Echo::Renderer::Submit(m_BlueShader, "u_ViewProjection", m_SquareVA, transform);
		
		//绘制三角形
		m_TriangleVA->AddVertexBuffer(m_TriangleVB);
		m_TriangleVA->SetIndexBuffer(m_TriangleIB);
		Echo::Renderer::Submit(m_Shader, "u_ViewProjection", m_TriangleVA);
		
		Echo::Renderer::EndScene();
	}
	
	virtual void OnKeyPressedEvent(int key) override
	{
		//左移/右移
		if (key == Qt::Key_A)
			m_CameraPosition.x += m_CameraMoveSpeed;
		else if (key == Qt::Key_D)
			m_CameraPosition.x -= m_CameraMoveSpeed;

		//上移/下移
		if (key == Qt::Key_W)
			m_CameraPosition.y -= m_CameraMoveSpeed;
		else if (key == Qt::Key_S)
			m_CameraPosition.y += m_CameraMoveSpeed;

		//旋转
		if (key == Qt::Key_Q)
			m_CameraRotation -= m_CameraRotationSpeed;
		if (key == Qt::Key_E)
			m_CameraRotation += m_CameraRotationSpeed;

		/////////////////////////////////////////////////////
		//移动矩形
		if (key == Qt::Key_Right)
			m_SquarePosition.x += m_CameraMoveSpeed;
		else if (key == Qt::Key_Left)
			m_SquarePosition.x -= m_CameraMoveSpeed;
		
		if (key == Qt::Key_Up)
			m_SquarePosition.y += m_CameraMoveSpeed;
		else if (key == Qt::Key_Down)
			m_SquarePosition.y -= m_CameraMoveSpeed;
		/////////////////////////////////////////////////////
	}

private:
	/// @brief 着色器
	std::shared_ptr<Echo::Shader> m_Shader;
	std::shared_ptr<Echo::Shader> m_BlueShader;
	/// @brief 顶点数组对象
	std::shared_ptr<Echo::VertexArray> m_TriangleVA;
	std::shared_ptr<Echo::VertexArray> m_SquareVA;
	/// @brief 顶点缓冲对象
	std::shared_ptr<Echo::VertexBuffer> m_SquareVB;
	std::shared_ptr<Echo::VertexBuffer> m_TriangleVB;
	/// @brief 顶点索引缓冲对象
	std::shared_ptr<Echo::IndexBuffer> m_TriangleIB;
	std::shared_ptr<Echo::IndexBuffer> m_SquareIB;
	
	/// @brief 相机
	Echo::Camera m_camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;

	glm::vec3 m_SquarePosition;
};

class SandBox : public Nest::Application
{
public:
	SandBox(int& argc, char** argv)
		: Nest::Application(argc, argv)
	{
	}
	~SandBox() {}

public:
	virtual void InitLayer()
	{
		Application::PushLayer(new ExampleLayer);
	}
};

Nest::Application* Nest::CreateApplication(int argc, char** argv)
{
	return new SandBox(argc, argv);
}
