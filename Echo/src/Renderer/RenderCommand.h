#pragma once
#include "RendererAPI.h"

namespace Echo {

	/// @brief RenderCommand类：渲染指令，此类中的所有方法都是静态的
	class RenderCommand
	{
	public:
		/// @brief 初始化场景
		static void Initialize();
		/// @brief 设置视口大小
		/// @param x 
		/// @param y 
		/// @param width 
		/// @param height 
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		/// @brief 设置清屏颜色
		/// @param color 
		static void SetClearColor(const glm::vec4& color);
		/// @brief 清空缓冲区
		static void Clear();

		/// @brief 根据顶点数组渲染图元
		/// @param vertexArray 顶点数组
		/// @param indexCount 索引数量 
		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);

	private:
		static RendererAPI* s_RendererAPI;
	};

}


