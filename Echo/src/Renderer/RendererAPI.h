#pragma once
#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Echo {

	/// @brief 渲染器API：此类为抽象类，提供渲染API的接口，具体实现由具体图形API子类实现
	class RendererAPI
	{
	public:
		/// @brief 枚举：图形API
		enum API
		{
			None = 0, OpenGL
		};

	public:
		/// @brief 获取图形API
		static API getAPI() { return s_API; }

		/// @brief 图形API初始化
		virtual void Init() = 0;
		/// @brief 设置视口大小
		/// @param x 
		/// @param y 
		/// @param width 
		/// @param height 
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/// @brief 设置清屏颜色
		/// @param color 
		virtual void SetClearColor(const glm::vec4& color) = 0;
		/// @brief 清空缓冲区
		virtual void Clear() = 0;

		/// @brief 根据顶点数组渲染图元
		/// @param vertexArray 顶点数组
		/// @param indexCount 索引数量
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

	private:
		/// @brief 图形API
		static API s_API;
	};

}


