#pragma once

#include "Echo/Renderer/RendererAPI.h"

namespace Echo {

	/// @brief OpenGL渲染API
	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		/// @brief 设置指定颜色缓冲区的清除值
		/// @param color 颜色
		virtual void SetClearColor(const glm::vec4& color) override;
		/// @brief 清除缓冲区到预设值
		/// @param mask 
		virtual void Clear(int mask) override;

		/// @brief 根据顶点数组渲染图元
		/// @param vertexArray 渲染用的顶点数组
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

}


