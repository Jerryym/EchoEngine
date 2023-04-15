#include "echopch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Echo {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}