#include "echopch.h"
#include "FrameBuffer.h"

#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Echo {

	Ref<FrameBuffer> FrameBuffer::CreateFrameBuffer(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(spec);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
