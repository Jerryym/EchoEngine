#pragma once
#include "RendererAPI.h"

namespace Echo {

	/// @brief RenderCommond类：渲染指令，此类中的所有方法都是静态的
	class RenderCommond
	{
	public:
		/// @brief 设置清屏颜色
		/// @param color 
		static void SetClearColor(const glm::vec4& color);
		/// @brief 清空缓冲区
		static void Clear();

	private:
		static RendererAPI* s_RendererAPI;
	};

}


