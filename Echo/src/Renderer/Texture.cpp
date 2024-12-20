#include "echopch.h"
#include "Texture.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Echo {
	
	Ref<Texture2D> Texture2D::CreateTexture(const std::string& sPath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(sPath);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
