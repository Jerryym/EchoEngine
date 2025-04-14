#pragma once
#include "Event.h"

namespace Echo {

	/// @brief 键盘事件
	class KeyEvent : public Event
	{
	public:
		unsigned int getKeyCode() const { return m_nKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(const unsigned int KeyCode)
			: m_nKeyCode(KeyCode) {}

		unsigned int m_nKeyCode; //键盘按键编号
	};

	/// @brief 键盘按下事件
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(unsigned int KeyCode, bool isRepeat = false)
			: KeyEvent(KeyCode), m_bIsRepeat(isRepeat) {}

		//是否重复按下
		bool IsRepeat() const { return m_bIsRepeat; }

		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "KeyPressedEvent: " << m_nKeyCode << ", repeat = " << m_bIsRepeat;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		bool m_bIsRepeat;
	};

	/// @brief 键盘释放事件
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(unsigned int KeyCode)
			: KeyEvent(KeyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "KeyReleasedEvent: " << m_nKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	/// @brief 键盘释放事件
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(unsigned int KeyCode)
			: KeyEvent(KeyCode) {}

	public:
		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "KeyTypedEvent: " << m_nKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
