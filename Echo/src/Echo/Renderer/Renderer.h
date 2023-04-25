#pragma once

#include "RenderCommond.h"

namespace Echo {

	class Renderer
	{
	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		/// @brief ��ʼ��Ļ��Ⱦ
		static void BeginScene();
		
		/// @brief ������Ļ��Ⱦ
		static void EndScene();

		/// @brief �ύ��Ⱦ�õĶ�������
		/// @param vertexArray ��Ⱦ�õĶ������� 
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};

}