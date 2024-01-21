#pragma once
#include "echopch.h"
#include "Core/EngineCore.h"

namespace Echo {

	/// @brief 事件类型枚举类
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	// 窗口操作
		KeyPressed, KeyReleased, KeyTyped,										// 键盘操作
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled		// 鼠标操作
	};

	/// @brief 事件过滤枚举
	enum EventCategory
	{
		None = 0,
		EventCategoryInput			= BIT(0),
		EventCategoryKeyboard		= BIT(1),
		EventCategoryMouse			= BIT(2),
		EventCategoryMouseButton	= BIT(3)
	};

	// 使用宏定义来替重复性代长语句
	#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategory() const override { return category; }


}
