#include "echopch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Echo {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		// Clear the color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		uint32_t iCount = vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, nullptr);
	}

}
