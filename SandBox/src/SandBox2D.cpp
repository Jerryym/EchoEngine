#include "SandBox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

SandBox2D::SandBox2D()
	: Echo::Layer("SandBox2D"), m_Camera(1600.f / 900.f, 1.0f)
{
}

void SandBox2D::OnAttach()
{
	//创建顶点数组对象
	m_CubeVA.reset(Echo::VertexArray::CreateVertexArray());
	float CubeVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // 0: 左下后
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // 1: 右下后
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // 2: 右上后
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // 3: 左上后
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // 4: 左下前
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // 5: 右下前
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // 6: 右上前
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f   // 7: 左上前
	};

	//创建顶点缓冲对象
	Echo::Ref<Echo::VertexBuffer> CubeVB;
	CubeVB.reset(Echo::VertexBuffer::CreateBuffer(CubeVertices, sizeof(CubeVertices)));
	Echo::BufferLayout CubeLayout = {
		{ Echo::ShaderDataType::Float3, "a_Position" },
		{ Echo::ShaderDataType::Float2, "a_TexCoord" }
	};
	CubeVB->SetLayout(CubeLayout);
	m_CubeVA->AddVertexBuffer(CubeVB);

	//创建索引缓冲对象
	Echo::Ref<Echo::IndexBuffer> Cube;
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
	Cube.reset(Echo::IndexBuffer::CreateBuffer(CubeIndices, sizeof(CubeIndices) / sizeof(uint32_t)));
	m_CubeVA->SetIndexBuffer(Cube);

	//创建着色器
	m_ShaderLib.Load("assets/shaders/Texture.glsl");
	m_Texture = Echo::Texture2D::CreateTexture("assets/textures/StuccoRoughCast.png");
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Echo::TimeStep ts)
{
	//更新相机
	m_Camera.OnUpdate(ts);

	//渲染
	Echo::Renderer::InitScene();
	Echo::RenderCommand::SetClearColor(glm::normalize(glm::vec4(112, 128, 144, 1)));
	Echo::RenderCommand::Clear();

	Echo::Renderer::BeginScene(m_Camera);

	m_Texture->Bind();
	auto textureShader = m_ShaderLib.Get("Texture");
	std::dynamic_pointer_cast<Echo::OpenGLShader>(textureShader)->Bind();
	std::dynamic_pointer_cast<Echo::OpenGLShader>(textureShader)->SetUniformInt("u_Texture", 0);
	Echo::Renderer::Submit(textureShader, m_CubeVA);

	Echo::Renderer::EndScene();
}

void SandBox2D::OnRenderUI()
{
}

void SandBox2D::OnEvent(Echo::Event& e)
{
	m_Camera.OnEvent(e);
}
