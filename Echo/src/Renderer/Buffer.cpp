#include "echopch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Echo {

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		CalculateOffsetAndStride();
	}

	void BufferLayout::CalculateOffsetAndStride()
	{
		uint32_t nOffset = 0;
		m_nStride = 0;
		for (auto& element : m_Elements)
		{
			element.m_nOffset = nOffset;
			nOffset += element.m_nSize;
			m_nStride += element.m_nSize;
		}
	}

	Ref<VertexBuffer> VertexBuffer::CreateBuffer(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(size);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::CreateBuffer(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::CreateBuffer(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
