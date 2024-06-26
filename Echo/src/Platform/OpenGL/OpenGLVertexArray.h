#pragma once
#include "Echo/Renderer/VertexArray.h"

namespace Echo {

	/// @brief OpenGL顶点数组
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void unBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) override;
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) override;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}

