#pragma once
#include "RendererAPI.h"

namespace Echo {

	/// @brief 渲染命令类
	class RenderCommond
	{
	public:
		/// @brief 设置指定颜色缓冲区的清除值
		/// @param color 
		static void SetClearColor(const glm::vec4& color);
		/// @brief 清除缓冲区
		/// @param mask 需要清除的缓冲区掩码
		static void Clear(int mask);

		/// @brief 根据顶点数组渲染图元
		/// @param vertexArray 
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

	private:
		static RendererAPI* s_RendererAPI;
	};

}


