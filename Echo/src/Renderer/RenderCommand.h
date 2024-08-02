#pragma once
#include "RendererAPI.h"

namespace Echo {

	/// @brief RenderCommand类：渲染指令，此类中的所有方法都是静态的
	class RenderCommand
	{
	public:
		/// @brief 设置清屏颜色
		/// @param color 
		static void SetClearColor(const glm::vec4& color);
		/// @brief 清空缓冲区
		static void Clear();
		/// @brief 根据顶点数组渲染图元
		/// @param vertexArray 
		static void DrawIndexed(const Ref<VertexArray>& vertexArray);

	private:
		static RendererAPI* s_RendererAPI;
	};

}


