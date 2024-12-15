#pragma once

namespace Echo {

	/// @brief 图形上下文
	class GraphicsContext
	{
	public:
		/// @brief 初始化
		virtual void Init() = 0;
		/// @brief 交换缓冲区
		virtual void SwapBuffers() = 0;
		/// @brief 销毁
		virtual void Destroy() = 0;
	};

}
