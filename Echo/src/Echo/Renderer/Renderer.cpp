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

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::string& name, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->setUniformMat4f(name, m_SceneData->ViewProjectionMatrix);
		shader->setUniformMat4f("u_Transform", transform);

		vertexArray->Bind();
		RenderCommond::DrawIndexed(vertexArray);
	}

}
