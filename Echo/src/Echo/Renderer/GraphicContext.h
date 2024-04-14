#pragma once

namespace Echo {

	/// @brief 渲染上下文
	class GraphicContext
	{
	public:
		/// @brief 渲染初始化
		virtual void Init() = 0;
		/// @brief 交换渲染缓存
		virtual void SwapBuffers() = 0;
	};

}
