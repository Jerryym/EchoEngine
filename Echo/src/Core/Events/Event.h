#pragma once
#include "echopch.h"
#include "Core.h"

namespace Echo {

	/// @brief 枚举类：事件类型
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,		//窗口事件
		AppTick, AppUpdate, AppRender,												//应用程序事件
		KeyPressed, KeyReleased, KeyTyped,											//键盘事件
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled			//键盘事件
	};

	/// @brief 枚举类：事件分类
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),	//应用程序事件
		EventCategoryInput			= BIT(1),	//输入事件
		EventCategoryKeyboard		= BIT(2),	//键盘事件
		EventCategoryMouse			= BIT(3),	//鼠标事件
		EventCategoryMouseButton	= BIT(4)	//鼠标按键事件
	};

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	virtual int GetEventCategory() const override { return category; }

	
	/// @brief 事件类，此类为抽象类，需要继承并实现其纯虚函数
	class Event
	{
	public:
		virtual ~Event() = default;

	public:
		/// @brief 获取事件类型
		virtual EventType GetEventType() const = 0;
		/// @brief 获取事件类型名称
		virtual const char* GetName() const = 0;
		/// @brief 获取事件分类
		virtual int GetEventCategory() const = 0;
		/// @brief 事件类型转换为字符串 
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			if (GetEventCategory() == category)
			{
				return true;
			}
			return false;
		}

		friend class EventDispatcher;
	protected:
		/// @brief 事件处理标识符(true-已处理, false-未处理)
		bool m_bHandled = false;
	};

	/// @brief 事件调度: 用于调度事件处理函数
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{}

		/// @brief 事件调度函数：调度一个特定类型的事件处理函数。如果事件类型匹配，则调用处理函数。
		template<typename T, typename F>
		bool Dispatcher(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_bHandled |= func(static_cast<T&>(m_Event));
				return true; //事件被成功调度并处理
			}
			return false;
		}

	private:
		/// @brief 事件对象引用
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}

}
