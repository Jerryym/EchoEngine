#pragma once

#include "echopch.h"
#include "Echo/Core.h"

namespace Echo {

	// 事件类型枚举类
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	// 窗口操作
		AppTick, AppUpdate, AppRender,											// App操作
		KeyPressed, KeyReleased, KeyTyped,										// 键盘操作
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

// 使用宏定义来替重复性代长语句
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategory() const override { return category; }
	
	class Event
	{
	public:
		virtual ~Event() = default;

		//获取事件类型
		virtual EventType GetEventType() const = 0;
		//获取事件类型名称
		virtual const char* GetName() const = 0;
		//过滤筛选事件
		virtual int GetCategory() const = 0;
		//将事件值转换为字符串
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			if (GetCategory() == category)
				return true;

			return false;
		}

		friend class EventDispatcher;
	protected:
		bool m_bHandled = false; // 事件是否已被处理
	};

	/// @brief 事件调度
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{

		}

		template<typename T, typename F>
		bool Dispatcher(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_bHandled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}
}

