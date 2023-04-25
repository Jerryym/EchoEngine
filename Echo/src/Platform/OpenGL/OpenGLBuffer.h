#pragma once
#include "Echo/Renderer/Buffer.h"

namespace Echo {

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void unBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override;

	private:
		uint32_t m_RendererID;
		BufferLayout m_layout;
	};


	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void unBind() const override;

		virtual uint32_t GetCount() const override { return m_iCount; }

	private:
		uint32_t m_RendererID;
		uint32_t m_iCount;		//Ë÷Òý»º³å¸öÊý
	};

}


