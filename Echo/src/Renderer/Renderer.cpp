#include "echopch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Echo {

	void Renderer::InitScene()
	{
		RenderCommand::InitScene();
	}

	void Renderer::WindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
