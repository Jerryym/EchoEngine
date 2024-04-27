#include "echopch.h"
#include "RenderCommond.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Echo {

	RendererAPI* RenderCommond::s_RendererAPI = new OpenGLRendererAPI;

	void RenderCommond::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommond::Clear(int mask)
	{
		s_RendererAPI->Clear(mask);
	}

	void RenderCommond::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}

}

