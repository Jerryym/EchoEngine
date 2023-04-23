#pragma once

#include "Echo/Renderer/RendererAPI.h"

namespace Echo {

	/// @brief OpenGL��ȾAPI
	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		/// @brief ���ô��ڱ���ɫ
		/// @param color ��ɫ
		virtual void SetClearColor(const glm::vec4& color) override;

		/// @brief �����������Ԥ��ֵ
		virtual void Clear() override;

		/// @brief ���ݶ���������ȾͼԪ
		/// @param vertexArray ��Ⱦ�õĶ�������
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

}


