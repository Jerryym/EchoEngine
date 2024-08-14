#pragma once
#include "Renderer/Buffer.h"

namespace Echo {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

	public:
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override { return m_layout; }

		virtual void SetData(const void* data, uint32_t size) override;

	private:
		uint32_t m_RendererID;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

	public:
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override { return m_iCount; }

	private:
		uint32_t m_RendererID;
		uint32_t m_iCount;
	};
}
