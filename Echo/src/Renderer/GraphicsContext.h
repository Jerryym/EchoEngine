#pragma once

namespace Echo {

	/// @brief 渲染上下文：此类为抽象类，需根据渲染平台实现具体子类
	class GraphicsContext
	{
	public:
		/// @brief 初始化
		virtual void Init() = 0;
		/// @brief 交换缓冲区
		virtual void SwapBuffers() = 0;
	};

}
