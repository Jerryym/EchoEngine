#pragma once

#include "Echo/Events/Event.h"

namespace Echo {

	/// @brief �����¼�
	class  KeyEvent : public Event
	{
	public:
		unsigned int getKeyCode() const { return m_nKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(const unsigned int KeyCode)
			: m_nKeyCode(KeyCode) {}

		unsigned int m_nKeyCode; //���̰������
	};

	/// @brief ���̰����¼�
	class  KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(unsigned int KeyCode, bool isRepeat = false)
			: KeyEvent(KeyCode), m_bIsRepeat(isRepeat) {}

		//�Ƿ��ظ�����
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

	/// @brief �����ͷ��¼�
	class  KeyReleasedEvent : public KeyEvent
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

	/// @brief �����ͷ��¼�
	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(unsigned int KeyCode)
			: KeyEvent(KeyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "KeyTypedEvent: " << m_nKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}