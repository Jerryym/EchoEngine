#pragma once

#include "Echo/Core.h"

#include <functional>
#include <string>

namespace Echo {

	// 事件类型枚举类
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	// 窗口操作
		AppTick, AppUpdate, AppRender,											// App操作
		KeyPressed, KeyReleased,												// 键盘操作
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled		// 鼠标操作
	};

	// 事件过滤枚举
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};


	class ECHO_API Event
	{
	public:
		Event();
		virtual ~Event() = default;

		//获取事件类型
		virtual EventType GetEventType() const = 0;
		//获取事件类型名称
		virtual const char* GetName() const = 0;
		//将事件值转换为字符串
		virtual std::string ToString() const = 0;
	};

}

