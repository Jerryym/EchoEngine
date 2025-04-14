#include "echopch.h"
#include "FrameBuffer.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Echo {

	Ref<FrameBuffer> FrameBuffer::CreateBuffer(const FrameBufferConfiguration& configuration)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPIType::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RenderAPIType::OpenGL:
				return CreateRef<OpenGLFrameBuffer>(configuration);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
