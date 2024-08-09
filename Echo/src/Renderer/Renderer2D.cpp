#include "echopch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Echo {

	static Renderer2DData* s_pData;

	void Renderer2D::Initialize()
	{
		s_pData = new Renderer2DData;
		//创建顶点数组对象
		s_pData->m_VertexArray = VertexArray::CreateVertexArray();
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
		s_pData->m_VertexArray->AddVertexBuffer(CubeVB);

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
		s_pData->m_VertexArray->SetIndexBuffer(Cube);

		//创建纹理
		uint32_t TextureData = 0xf0ffffff;
		s_pData->m_Texture = Texture2D::Create(1, 1);
		s_pData->m_Texture->SetData(&TextureData, sizeof(uint32_t));

		//创建着色器
		s_pData->m_Shader = Shader::Create("assets/shaders/Texture.glsl");
		s_pData->m_Shader->Bind();
		s_pData->m_Shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::ShutDown()
	{
		delete s_pData;
	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		s_pData->m_Shader->Bind();
		s_pData->m_Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_pData->m_Shader->SetFloat4("u_Color", color);
		s_pData->m_Texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_pData->m_Shader->SetMat4("u_Transform", transform);
		s_pData->m_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_pData->m_VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		s_pData->m_Shader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_pData->m_Shader->SetMat4("u_Transform", transform);

		s_pData->m_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_pData->m_VertexArray);
	}

}
