#include "echopch.h"
#include "Renderer.h"

namespace Echo {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(const Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::string& name, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->setUniformMat4f(name, m_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommond::DrawIndexed(vertexArray);
	}

}
