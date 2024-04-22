#include "echopch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Echo {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray;
		}

		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
