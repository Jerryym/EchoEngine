#include "echopch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Echo {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray;
		}

		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}