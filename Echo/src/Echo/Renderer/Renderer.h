#pragma once

#include "RenderCommond.h"

namespace Echo {

	class Renderer
	{
	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		/// @brief 开始屏幕渲染
		static void BeginScene();
		
		/// @brief 结束屏幕渲染
		static void EndScene();

		/// @brief 提交渲染用的顶点数组
		/// @param vertexArray 渲染用的顶点数组 
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};

}