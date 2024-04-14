#pragma once
#include "Echo/Renderer/Buffer.h"

namespace Echo {

	/// @brief OpenGL顶点缓冲
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

	public:
		/// @brief 绑定对应顶点缓冲对象
		virtual void Bind() const override;
		/// @brief 解绑释放对应顶点缓冲对象
		virtual void UnBind() const override;

	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

	public:
		/// @brief 绑定对应顶点缓冲对象
		virtual void Bind() const override;
		/// @brief 解绑释放对应顶点缓冲对象
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override { return m_iCount; }

	private:
		uint32_t m_RendererID;
		/// @brief 索引缓冲个数
		uint32_t m_iCount;
	};

}


