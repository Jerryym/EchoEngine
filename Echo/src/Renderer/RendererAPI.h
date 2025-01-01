#pragma once
#include "Core.h"

#include "Renderer/VertexArray.h"
#include <glm/glm.hpp>

namespace Echo {

	/// @brief 渲染API类型
	enum class RenderAPIType
	{
		None = 0, OpenGL
	};

	/// @brief 渲染器API
	class RendererAPI
	{
	public:
		/// @brief 获取渲染器API类型
		/// @return 
		static RenderAPIType GetAPIType() { return s_APIType; }
		/// @brief 设置渲染器API类型
		/// @param type 
		static void SetAPIType(RenderAPIType type) { s_APIType = type; }

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
		/// @param vertexArray 渲染用的顶点数组
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

	private:
		/// @brief 渲染API类型
		inline static RenderAPIType s_APIType = RenderAPIType::OpenGL;
	};

}
