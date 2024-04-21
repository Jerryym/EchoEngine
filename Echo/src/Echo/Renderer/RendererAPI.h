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
		/// @brief 设置指定颜色缓冲区的清除值
		/// @param color 颜色
		virtual void SetClearColor(const glm::vec4& color) = 0;
		/// @brief 清除缓冲区到预设值
		/// @param mask 需要清除的缓冲区掩码
		virtual void Clear(int mask) = 0;
		
		/// @brief 根据顶点数组渲染图元
		/// @param vertexArray 渲染用的顶点数组
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return s_API; }

	private:
		/// @brief 图形API
		static API s_API;
	};

}

