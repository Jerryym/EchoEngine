#include "echopch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Echo {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear(int mask)
	{
		glClear(mask);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		uint32_t iCount = vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, nullptr);
	}

}
