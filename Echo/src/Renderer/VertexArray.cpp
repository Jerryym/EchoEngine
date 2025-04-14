#include "echopch.h"
#include "VertexArray.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Echo {

	Ref <VertexArray> VertexArray::CreateVertexArray()
	{
		switch (RendererAPI::GetAPIType())
		{
			case RenderAPIType::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RenderAPIType::OpenGL:
				return CreateRef<OpenGLVertexArray>();
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
