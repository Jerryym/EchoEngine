#pragma once
#include "echopch.h"
#include "Core/Events/Event.h"

namespace Echo {

	/// @brief 窗口属性
	struct sWindowProp 
	{
		uint32_t m_iWidth;		//窗口宽
		uint32_t m_iHeight;		//窗口高
		std::string m_sTitle;	//窗口标题

		sWindowProp(const std::string& sTitle = "Echo Engine", uint32_t iWidth = 1600, uint32_t iHeight = 900)
			: m_iWidth(iWidth), m_iHeight(iHeight), m_sTitle(sTitle)
		{}

	};

	/// @brief 主窗口类，此类为抽象类，需要继承并实现其纯虚函数
	class MainWindow 
	{
	public:
		/// @brief 事件回调函数
		using EventCallBackFun = std::function<void(Event&)>;

		virtual ~MainWindow() {}

		/// @brief 创建主窗口
		/// @param prop 窗口属性
		/// @return 
		static Scope<MainWindow> CreateMainWindow(const sWindowProp& prop = sWindowProp());

	public:
		/// @brief 窗口更新
		virtual void OnUpdate() = 0;

		/// @brief 获取窗口宽度
		virtual uint32_t GetWidth() const = 0;
		/// @brief 获取窗口高度
		virtual uint32_t GetHeight() const = 0;
		/// @brief 获取窗口标题
		virtual const std::string& GetTitle() const = 0;

		/// @brief 设置垂直同步
		/// @param bEnable true-开启，false-关闭
		virtual void SetVSync(bool bEnable) = 0;
		/// @brief 获取垂直同步状态
		/// @return true-开启，false-关闭
		virtual bool IsVSync() const = 0;

		/// @brief 获取当前活动窗口
		/// @return 当前活动窗口指针
		virtual void* GetNativeWindow() const = 0;

		/// @brief 设置事件回调函数
		/// @param callback 
		virtual void SetEventCallBack(const EventCallBackFun& callback) = 0;
	};

}
