#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Echo {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

	public:
		/// @brief ���ô��ڱ���ɫ
		/// @param color ��ɫ
		virtual void SetClearColor(const glm::vec4& color) = 0;
		
		/// @brief �����������Ԥ��ֵ
		virtual void Clear() = 0;
		
		/// @brief ���ݶ���������ȾͼԪ
		/// @param vertexArray ��Ⱦ�õĶ�������
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return s_API; }

	private:
		static API s_API;	//ͼ��API
	};

}

