#include "echopch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Echo {

	/// @brief 四边形顶点信息
	typedef struct QuadVertexInfo
	{
		/// @brief 坐标
		glm::vec3 m_Position;
		/// @brief 颜色
		glm::vec4 m_Color;
		/// @brief 纹理坐标
		glm::vec2 m_TexCoord;
		/// @brief 纹理索引
		float m_rTexIndex = 0.0f;
		/// @brief 平铺因子
		float m_rTilingFactor = 1.0f;
	}QuadVertexInfo;

	/// @brief 2D渲染数据
	typedef struct Renderer2D_Data
	{
		/// @brief 渲染四边形最大数量
		static const uint32_t m_iMaxQuadCount = 20000;
		/// @brief 渲染四边形最大顶点数
		static const uint32_t m_iMaxVertices = m_iMaxQuadCount * 4;
		/// @brief 渲染四边形最大顶点索引数
		static const uint32_t m_iMaxIndices = m_iMaxQuadCount * 6;
		/// @brief 渲染四边形最大纹理槽
		static const uint32_t m_iMaxTextureSlots = 32;

		/// @brief 顶点数组对象
		Ref<VertexArray> m_VAO;
		/// @brief 顶点缓冲对象
		Ref<VertexBuffer> m_VBO;
		/// @brief 2D纹理（默认为白色纹理）
		Ref<Texture2D> m_Texture;
		/// @brief 着色器
		Ref<Shader> m_Shader;

		/// @brief 四边形顶点索引
		uint32_t m_iQuadIndexCount = 0;
		/// @brief 顶点缓冲基准地址
		QuadVertexInfo* m_pQuadVertexBufferBase = nullptr;
		/// @brief 顶点缓冲指针
		QuadVertexInfo* m_pQuadVertexBufferPtr = nullptr;

		/// @brief 纹理槽
		std::array<Ref<Texture2D>, m_iMaxTextureSlots> m_TextureSlots;
		/// @brief 当前纹理槽
		uint32_t m_iTextureSlotIndex = 1; //0 == white texture

		/// @brief 四边形顶点坐标
		glm::vec4 m_QuadVertexPositions[4];

		/// @brief 渲染统计数据
		RenderStatistics m_Stats;

	}Renderer2D_Data;

	static Renderer2D_Data* s_pData;

	void Renderer2D::Initialize()
	{
		s_pData = new Renderer2D_Data;

		//创建顶点数组对象
		s_pData->m_VAO = VertexArray::CreateVertexArray();

		//创建顶点缓冲对象
		s_pData->m_VBO = VertexBuffer::CreateBuffer(s_pData->m_iMaxVertices * sizeof(QuadVertexInfo));
		BufferLayout QuadLayout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor"}
		};
		s_pData->m_VBO->SetLayout(QuadLayout);
		s_pData->m_VAO->AddVertexBuffer(s_pData->m_VBO);
		s_pData->m_pQuadVertexBufferBase = new QuadVertexInfo[s_pData->m_iMaxVertices];

		//创建索引缓冲对象
		uint32_t* QuadIndices = new uint32_t[s_pData->m_iMaxIndices];
		uint32_t iOffset = 0;
		for (uint32_t i = 0; i < s_pData->m_iMaxIndices; i+=6)
		{
			QuadIndices[i + 0] = iOffset + 0;
			QuadIndices[i + 1] = iOffset + 1;
			QuadIndices[i + 2] = iOffset + 2;

			QuadIndices[i + 3] = iOffset + 2;
			QuadIndices[i + 4] = iOffset + 3;
			QuadIndices[i + 5] = iOffset + 0;

			iOffset += 4;
		}
		Ref<IndexBuffer> QuadIBO = IndexBuffer::CreateBuffer(QuadIndices, s_pData->m_iMaxIndices);
		s_pData->m_VAO->SetIndexBuffer(QuadIBO);
		delete[] QuadIndices;

		//创建纹理
		uint32_t TextureData = 0xffffffff;
		s_pData->m_Texture = Texture2D::Create(1, 1);
		s_pData->m_Texture->SetData(&TextureData, sizeof(uint32_t));
		int32_t samplers[s_pData->m_iMaxTextureSlots];
		for (uint32_t i = 0; i < s_pData->m_iMaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		//创建着色器
		s_pData->m_Shader = Shader::Create("assets/shaders/Texture.glsl");
		s_pData->m_Shader->Bind();
		s_pData->m_Shader->SetIntArray("u_Textures", samplers, s_pData->m_iMaxTextureSlots);

		//初始化纹理槽
		s_pData->m_TextureSlots[0] = s_pData->m_Texture;

		//初始化四边形顶点坐标
		s_pData->m_QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_pData->m_QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_pData->m_QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_pData->m_QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::ShutDown()
	{
		delete s_pData;
	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		//绑定Shader
		s_pData->m_Shader->Bind();
		s_pData->m_Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		//每次开始渲染场景使，初始化顶点索引数量、顶点缓冲指针地址指向和当前纹理槽索引
		s_pData->m_iQuadIndexCount = 0;
		s_pData->m_pQuadVertexBufferPtr = s_pData->m_pQuadVertexBufferBase;
		s_pData->m_iTextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		// 计算当前绘制需要的顶点数据个数
		uint32_t iDataSize = (uint8_t*)s_pData->m_pQuadVertexBufferPtr - (uint8_t*)s_pData->m_pQuadVertexBufferBase;
		s_pData->m_VBO->SetData(s_pData->m_pQuadVertexBufferBase, iDataSize);

		//刷新场景
		RefreshScene();
	}

	void Renderer2D::RefreshScene()
	{
		//绑定纹理
		for (uint32_t i = 0; i < s_pData->m_iTextureSlotIndex; i++)
		{
			s_pData->m_TextureSlots[i]->Bind(i);
		}
		RenderCommand::DrawIndexed(s_pData->m_VAO, s_pData->m_iQuadIndexCount);
		s_pData->m_Stats.m_iDrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		/*
		绘制顺序:
									3-------2
									|		|
									|		|
									|		|
									0-------1
		*/
		if (s_pData->m_iQuadIndexCount >= Renderer2D_Data::m_iMaxIndices)
		{
			RefreshStats();
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[0];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 0.0f, 0.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = 0.0f;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = 1.0f;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[1];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 1.0f, 0.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = 0.0f;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = 1.0f;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[2];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 1.0f, 1.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = 0.0f;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = 1.0f;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[3];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 0.0f, 1.0f };
		s_pData->m_pQuadVertexBufferPtr++;

		// 更新索引计数（6 == 绘制一个四边形需要6个索引）
		s_pData->m_iQuadIndexCount += 6;

		s_pData->m_Stats.m_iQuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rTilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, rTilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rTilingFactor, const glm::vec4& tintColor)
	{
		/*
		绘制顺序:
									3-------2
									|		|
									|		|
									|		|
									0-------1
		*/
		if (s_pData->m_iQuadIndexCount >= Renderer2D_Data::m_iMaxIndices)
		{
			RefreshStats();
		}

		float rTextureIndex = 0.0f;
		for (uint32_t i = 1; i < s_pData->m_iTextureSlotIndex; i++)
		{
			if (*s_pData->m_TextureSlots[i].get() == *texture.get())// 如果当前纹理已经存储在纹理槽，就直接读取
			{
				rTextureIndex = (float)i;
				break;
			}
		}
		if (rTextureIndex == 0.0f)
		{
			rTextureIndex = (float)s_pData->m_iTextureSlotIndex;
			s_pData->m_TextureSlots[s_pData->m_iTextureSlotIndex] = texture;
			s_pData->m_iTextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		constexpr glm::vec4 color = glm::vec4(1.0f);
		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[0];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 0.0f, 0.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = rTextureIndex;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = rTilingFactor;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[1];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 1.0f, 0.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = rTextureIndex;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = rTilingFactor;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[2];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 1.0f, 1.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = rTextureIndex;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = rTilingFactor;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[3];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 0.0f, 1.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = rTextureIndex;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = rTilingFactor;
		s_pData->m_pQuadVertexBufferPtr++;

		// 更新索引计数（6 == 绘制一个四边形需要6个索引）
		s_pData->m_iQuadIndexCount += 6;

		s_pData->m_Stats.m_iQuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rRotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rRotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rRotation, const glm::vec4& color)
	{
		/*
		绘制顺序:
									3-------2
									|		|
									|		|
									|		|
									0-------1
		*/
		if (s_pData->m_iQuadIndexCount >= Renderer2D_Data::m_iMaxIndices)
		{
			RefreshStats();
		}

		// 设置transform
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rRotation), { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[0];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 0.0f, 0.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = 0.0f;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = 1.0f;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[1];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 1.0f, 0.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = 0.0f;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = 1.0f;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[2];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 1.0f, 1.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = 0.0f;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = 1.0f;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[3];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 0.0f, 1.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = 0.0f;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = 1.0f;
		s_pData->m_pQuadVertexBufferPtr++;

		// 更新索引计数（6 == 绘制一个四边形需要6个索引）
		s_pData->m_iQuadIndexCount += 6;

		s_pData->m_Stats.m_iQuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rRotation, const Ref<Texture2D>& texture, float rTilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rRotation, texture, rTilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rRotation, const Ref<Texture2D>& texture, float rTilingFactor, const glm::vec4& tintColor)
	{
		/*
		绘制顺序:
									3-------2
									|		|
									|		|
									|		|
									0-------1
		*/
		if (s_pData->m_iQuadIndexCount >= Renderer2D_Data::m_iMaxIndices)
		{
			RefreshStats();
		}

		float rTextureIndex = 0.0f;
		for (uint32_t i = 1; i < s_pData->m_iTextureSlotIndex; i++)
		{
			if (*s_pData->m_TextureSlots[i].get() == *texture.get())// 如果当前纹理已经存储在纹理槽，就直接读取
			{
				rTextureIndex = (float)i;
				break;
			}
		}
		if (rTextureIndex == 0.0f)
		{
			rTextureIndex = (float)s_pData->m_iTextureSlotIndex;
			s_pData->m_TextureSlots[s_pData->m_iTextureSlotIndex] = texture;
			s_pData->m_iTextureSlotIndex++;
		}

		// 设置transform
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rRotation), { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		constexpr glm::vec4 color = glm::vec4(1.0f);
		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[0];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 0.0f, 0.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = rTextureIndex;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = rTilingFactor;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[1];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 1.0f, 0.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = rTextureIndex;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = rTilingFactor;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[2];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 1.0f, 1.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = rTextureIndex;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = rTilingFactor;
		s_pData->m_pQuadVertexBufferPtr++;

		s_pData->m_pQuadVertexBufferPtr->m_Position = transform * s_pData->m_QuadVertexPositions[3];
		s_pData->m_pQuadVertexBufferPtr->m_Color = color;
		s_pData->m_pQuadVertexBufferPtr->m_TexCoord = { 0.0f, 1.0f };
		s_pData->m_pQuadVertexBufferPtr->m_rTexIndex = rTextureIndex;
		s_pData->m_pQuadVertexBufferPtr->m_rTilingFactor = rTilingFactor;
		s_pData->m_pQuadVertexBufferPtr++;

		// 更新索引计数（6 == 绘制一个四边形需要6个索引）
		s_pData->m_iQuadIndexCount += 6;

		s_pData->m_Stats.m_iQuadCount++;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_pData->m_Stats, 0, sizeof(RenderStatistics));
	}

	RenderStatistics Renderer2D::GetStats()
	{
		return s_pData->m_Stats;
	}

	void Renderer2D::RefreshStats()
	{
		EndScene();

		s_pData->m_iQuadIndexCount = 0;
		s_pData->m_pQuadVertexBufferPtr = s_pData->m_pQuadVertexBufferBase;
		s_pData->m_iTextureSlotIndex = 1;
	}

}
