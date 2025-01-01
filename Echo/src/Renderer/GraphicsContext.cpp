#include "echopch.h"
#include "GraphicsContext.h"

#include "Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Echo {

	Ref<GraphicsContext> GraphicsContext::CreateContext(uint32_t nWidth, uint32_t nHeight, const std::string& sTitle)
	{
		switch (RendererAPI::GetAPIType())
		{
		case RenderAPIType::None:			return nullptr;
		case RenderAPIType::OpenGL:			return CreateRef<OpenGLContext>(nWidth, nHeight, sTitle);
		}
		ECHO_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<GraphicsContext> GraphicsContext::CreateContext(uint32_t nWidth, uint32_t nHeight, const std::string& sTitle, bool bShowWindow)
	{
		switch (RendererAPI::GetAPIType())
		{
		case RenderAPIType::None:			return nullptr;
		case RenderAPIType::OpenGL:			return CreateRef<OpenGLContext>(nWidth, nHeight, sTitle, bShowWindow);
		}
		ECHO_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
