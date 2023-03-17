#pragma once

#include "echopch.h"
#include "Core.h"
#include "Events/Event.h"


namespace Echo {

	/// @brief 窗口属性
	typedef struct sWindowProps
	{
		unsigned int m_nWidth;		//窗口宽
		unsigned int m_nHeight;		//窗口高
		std::string m_strTitle;		//窗口标题

		sWindowProps(unsigned int width = 1600, unsigned int height = 900,
			const std::string& title = "Echo Engine")
			: m_nWidth(width), m_nHeight(height), m_strTitle(title)
		{

		}
	}sWindowProps;


	/// @brief 基于桌面系统的 Window 接口
	class ECHO_API Window
	{
	public:
		/// @brief 事件回调函数
		using EventCallBackFun = std::function<void(Event&)>;
		
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		////////////////////////////////////////////////////////////////////
		// 窗口属性
		/// @brief 设置事件回调函数
		/// @param callback 
		virtual void SetEventCallBack(const EventCallBackFun& callback) = 0;
		
		/// @brief 设置垂直同步
		/// @param enabled 
		virtual void SetVSync(bool enabled) = 0;

		/// @brief 是否开启了垂直同步
		/// @return 垂直同步设置状态
		virtual bool IsVSync() const = 0;
		////////////////////////////////////////////////////////////////////

		/// @brief 获取当前活动窗口
		/// @return 当前活动窗口指针
		virtual void* GetNativeWindow() const = 0;

		/// @brief 创建窗口
		/// @param props 窗口属性
		/// @return 窗口指针
		static Window* Create(const sWindowProps& props = sWindowProps());

	};

}