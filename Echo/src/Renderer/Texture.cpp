#include "echopch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Echo {

	Ref<Texture2D> Texture2D::CreateTexture(const std::string& sPath)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPIType::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RenderAPIType::OpenGL:
				return std::make_shared<OpenGLTexture2D>(sPath);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}
