#include "echopch.h"
#include "RenderCommond.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Echo {

	RendererAPI* RenderCommond::s_RendererAPI = new OpenGLRendererAPI;

	void RenderCommond::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommond::Clear()
	{
		s_RendererAPI->Clear();
	}

}
