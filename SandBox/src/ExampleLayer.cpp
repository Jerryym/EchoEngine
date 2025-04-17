#include "pch.h"
#include "ExampleLayer.h"

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>

namespace SandBoxApp {

	ExampeleLayer::ExampeleLayer()
		: Echo::Layer("ExampleLayer")
	{
		m_Camera.SetPosition(glm::vec3(0, 0, 10));
		m_Camera.SetPerspectiveMat(45.f, 1600.0f, 900.0f, 0.1f, 1000.0f);
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
		const float speed = 5.0f;
		if (Echo::Input::IsKeyPressed(Echo::Key::KeyCode::W))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0, 0, -speed * ts.GetSeconds()));
		if (Echo::Input::IsKeyPressed(Echo::Key::KeyCode::S))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0, 0, speed * ts.GetSeconds()));
		if (Echo::Input::IsKeyPressed(Echo::Key::KeyCode::A))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-speed * ts.GetSeconds(), 0, 0));
		if (Echo::Input::IsKeyPressed(Echo::Key::KeyCode::D))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(speed * ts.GetSeconds(), 0, 0));

		//初始化渲染器
		Echo::Renderer::InitRenderer();

		Echo::RenderCommand::SetClearColor(glm::normalize(glm::vec4(112, 128, 144, 1)));
		Echo::RenderCommand::Clear();

		Echo::Renderer::BeginScene(m_Camera);
		
		auto cubeShader = m_ShaderLib.Get("CubeShader");
		cubeShader->SetFloat3("u_CameraPos", m_Camera.GetPosition());
		cubeShader->SetFloat("u_Metallic", 1.0f);//金属度
		cubeShader->SetFloat("u_Roughness", 0.0f);//粗糙度
		cubeShader->SetFloat("u_AO", 1.0f);//环境遮蔽
		m_Texture->Bind();
		Echo::Renderer::Submit(cubeShader, m_CubeVA);
		
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
			//Position           //TexCoord
			//正面
			-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

			//背面
			0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
		   -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
		   -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,    0.0f, 1.0f,

			//左侧面
			-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,

			//右侧面
			0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,    0.0f, 1.0f,

			//顶面
			-0.5f,  0.5f,  0.5f,    0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,

			//底面
			-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,    1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,    0.0f, 1.0f
		};

		//创建顶点缓冲对象
		Echo::Ref<Echo::VertexBuffer> CubeVB = Echo::VertexBuffer::CreateBuffer(CubeVertices, sizeof(CubeVertices));
		Echo::BufferLayout CubeLayout = {
			{ Echo::ShaderDataType::Float3, "a_Position" },
			{ Echo::ShaderDataType::Float2, "a_TexCoord" }
		};
		CubeVB->SetLayout(CubeLayout);
		m_CubeVA->AddVertexBuffer(CubeVB);

		//创建索引缓冲对象
		uint32_t CubeIndices[] = {
			//正面
			0, 1, 2, 2, 3, 0,
			//背面
			4, 5, 6, 6, 7, 4,
			//左侧面
			8, 9,10,10,11, 8,
			//右侧面
			12,13,14,14,15,12,
			//顶面
			16,17,18,18,19,16,
			//底面
			20,21,22,22,23,20
		};
		Echo::Ref<Echo::IndexBuffer> Cube = Echo::IndexBuffer::CreateBuffer(CubeIndices, sizeof(CubeIndices) / sizeof(uint32_t));
		m_CubeVA->SetIndexBuffer(Cube);

		//创建着色器
		auto shader = m_ShaderLib.Load("CubeShader", "assets/shaders/BasicPBR.glsl");
		//创建纹理
		m_Texture = Echo::Texture2D::CreateTexture("assets/textures/Moon.png");
		shader->Bind();
		shader->SetInt("u_Texture", 0);
	}

}
