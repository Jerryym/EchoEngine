#pragma once

#include "echopch.h"
#include "Echo/Core.h"

namespace Echo {

	// �¼�����ö����
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	// ���ڲ���
		AppTick, AppUpdate, AppRender,											// App����
		KeyPressed, KeyReleased, KeyTyped,										// ���̲���
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled		// ������
	};

	// �¼�����ö��
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

// ʹ�ú궨�������ظ��Դ������
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategory() const override { return category; }
	
	class ECHO_API Event
	{
	public:
		virtual ~Event() = default;

		//��ȡ�¼�����
		virtual EventType GetEventType() const = 0;
		//��ȡ�¼���������
		virtual const char* GetName() const = 0;
		//����ɸѡ�¼�
		virtual int GetCategory() const = 0;
		//���¼�ֵת��Ϊ�ַ���
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			if (GetCategory() == category)
				return true;

			return false;
		}

		friend class EventDispatcher;
	protected:
		bool m_bHandled = false; // �¼��Ƿ��ѱ�����
	};

	/// @brief �¼�����
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

