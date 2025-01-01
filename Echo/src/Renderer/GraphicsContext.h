#pragma once
#include "Core.h"

namespace Echo {

	/// @brief 图形上下文
	class ECHO_API GraphicsContext
	{
	public:
		/// @brief 创建图形上下文
		/// @param nWidth 窗口宽度
		/// @param nHeight 窗口高度
		/// @param sTitle 标题
		/// @return 返回当前渲染API的图形上下文
		static Ref<GraphicsContext> CreateContext(uint32_t nWidth, uint32_t nHeight, const std::string& sTitle);
		/// @brief 创建图形上下文
		/// @param nWidth 窗口宽度
		/// @param nHeight 窗口高度
		/// @param sTitle 标题
		/// @param bShowWindow 是否显示窗口
		/// @return 返回当前渲染API的图形上下文
		static Ref<GraphicsContext> CreateContext(uint32_t nWidth, uint32_t nHeight, const std::string& sTitle, bool bShowWindow);

	public:
		/// @brief 初始化
		virtual void Init() = 0;
		/// @brief 设置当前上下文
		virtual void MakeCurrent() = 0;
		/// @brief 交换缓冲区
		virtual void SwapBuffers() = 0;
		/// @brief 销毁
		virtual void Destroy() = 0;
		// @brief 获取窗口句柄
		virtual void* GetWindowHandle() = 0;
	};

}
