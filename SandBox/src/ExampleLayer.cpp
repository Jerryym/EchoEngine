#include "pch.h"
#include "ExampleLayer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace SandBoxApp {

	ExampeleLayer::ExampeleLayer()
		: Echo::Layer("ExampleLayer")
	{
		m_Camera.SetPosition(glm::vec3(0.0f, -100.0f, 0.0));
		m_Camera.SetPerspectiveMat(30.f, 1600.0f, 900.0f, 0.1f, 1000.0f);
		DrawCube();
	}

	ExampeleLayer::~ExampeleLayer()
	{
	}

	void ExampeleLayer::OnAttach()
	{
	}

	void ExampeleLayer::OnDetach()
	{
	}

	void ExampeleLayer::OnUpdate(Echo::TimeStep ts)
	{
		Echo::RenderCommand::SetClearColor(glm::normalize(glm::vec4(112, 128, 144, 1)));
		Echo::RenderCommand::Clear();

		Echo::Renderer::BeginScene(m_Camera);
		m_Shader->Bind();
		m_Shader->SetFloat3("u_Color", m_CubeColor);
		Echo::Renderer::Submit(m_Shader, m_CubeVA);
		Echo::Renderer::EndScene();
	}

	void ExampeleLayer::OnRenderUI()
	{
	}

	void ExampeleLayer::OnEvent(Echo::Event& e)
	{
	}

	void ExampeleLayer::DrawCube()
	{
		//创建顶点数组对象
		m_CubeVA = Echo::VertexArray::CreateVertexArray();
		float CubeVertices[] = {
			-0.5f, -0.5f, -0.5f,  // 0: 左下后
			 0.5f, -0.5f, -0.5f,  // 1: 右下后
			 0.5f,  0.5f, -0.5f,  // 2: 右上后
			-0.5f,  0.5f, -0.5f,  // 3: 左上后
			-0.5f, -0.5f,  0.5f,  // 4: 左下前
			 0.5f, -0.5f,  0.5f,  // 5: 右下前
			 0.5f,  0.5f,  0.5f,  // 6: 右上前
			-0.5f,  0.5f,  0.5f   // 7: 左上前
		};

		//创建顶点缓冲对象
		Echo::Ref<Echo::VertexBuffer> CubeVB = Echo::VertexBuffer::CreateBuffer(CubeVertices, sizeof(CubeVertices));
		Echo::BufferLayout CubeLayout = {
			{ Echo::ShaderDataType::Float3, "a_Position" },
		};
		CubeVB->SetLayout(CubeLayout);
		m_CubeVA->AddVertexBuffer(CubeVB);

		//创建索引缓冲对象
		uint32_t CubeIndices[] = {
			// 背面
			0, 1, 2,
			2, 3, 0,

			// 正面
			4, 5, 6,
			6, 7, 4,

			// 左面
			0, 3, 7,
			7, 4, 0,

			// 右面
			1, 5, 6,
			6, 2, 1,

			// 底面
			0, 4, 5,
			5, 1, 0,

			// 顶面
			3, 2, 6,
			6, 7, 3
		};
		Echo::Ref<Echo::IndexBuffer> Cube = Echo::IndexBuffer::CreateBuffer(CubeIndices, sizeof(CubeIndices) / sizeof(uint32_t));
		m_CubeVA->SetIndexBuffer(Cube);

		//创建着色器
		std::string vertexShader = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;

				void main()
				{
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
				}
			)";

		std::string fragmentShader = R"(
				#version 330 core
			
				layout(location = 0) out vec4 color;

				in vec3 v_Position;
			
				uniform vec3 u_Color;

				void main()
				{
					color = vec4(u_Color, 1.0);
				}
			)";
		m_Shader = Echo::Shader::Create("CubeShader", vertexShader, fragmentShader);
	}

}
