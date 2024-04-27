#include "echopch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Echo {

	/// @brief 着色器数据类型转换为OpenGL基本数据类型
	/// @param type 
	/// @return 
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Echo::ShaderDataType::Float:		return GL_FLOAT;
		case Echo::ShaderDataType::Float2:		return GL_FLOAT;
		case Echo::ShaderDataType::Float3:		return GL_FLOAT;
		case Echo::ShaderDataType::Float4:		return GL_FLOAT;
		case Echo::ShaderDataType::Mat3:		return GL_FLOAT_MAT3;
		case Echo::ShaderDataType::Mat4:		return GL_FLOAT_MAT4;
		case Echo::ShaderDataType::Int:			return GL_INT;
		case Echo::ShaderDataType::Int2:		return GL_INT;
		case Echo::ShaderDataType::Int3:		return GL_INT;
		case Echo::ShaderDataType::Int4:		return GL_INT;
		case Echo::ShaderDataType::Bool:		return GL_BOOL;
		}

		ECHO_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::unBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer)
	{
		uint32_t iSize = vertexbuffer->GetLayout().GetElements().size();
		ECHO_CORE_ASSERT(iSize, "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexbuffer->Bind();

		unsigned int iIndex = 0;
		const auto& layout = vertexbuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(iIndex);
			glVertexAttribPointer(iIndex, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.m_enType),
				element.m_bNormalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				reinterpret_cast<const void*>(element.m_nOffset));
			iIndex++;
		}

		m_VertexBuffers.push_back(vertexbuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer)
	{
		glBindVertexArray(m_RendererID);
		indexbuffer->Bind();

		m_IndexBuffer = indexbuffer;
	}

}
