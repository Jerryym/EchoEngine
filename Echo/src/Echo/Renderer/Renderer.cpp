#include "echopch.h"
#include "Renderer.h"

namespace Echo {

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommond::DrawIndexed(vertexArray);
	}

}