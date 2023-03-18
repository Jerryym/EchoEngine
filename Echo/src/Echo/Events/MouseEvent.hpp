#pragma once

#include "Echo/Events/Event.h"

// ����¼�
namespace Echo {

	/// @brief ����ƶ��¼�
	class ECHO_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_rPositionX(x), m_rPositionY(y) {}

		float getX() const { return m_rPositionX; }
		float getY() const { return m_rPositionY; }

		std::string ToString() const override
		{
			// ʹ�� std::stringstream ʵ����������ת��
			std::stringstream ss{};
			ss << "MouseMovedEvent: " << m_rPositionX << ", " << m_rPositionY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private: 
		float m_rPositionX;
		float m_rPositionY;
	};

	/// @brief �������¼�
	class ECHO_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			: m_rOffsetX(x), m_rOffsetY(y) {}

		float getXOffset() const { return m_rOffsetX; }
		float getYOffset() const { return m_rOffsetY; }

		std::string ToString() const override
		{
			// ʹ�� std::stringstream ʵ����������ת��
			std::stringstream ss{};
			ss << "MouseScrolledEvent: " << m_rOffsetX << ", " << m_rOffsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_rOffsetX;	// x��ƫ��
		float m_rOffsetY;	// y��ƫ��
	};

	/// @brief ��갴ť�¼�
	class ECHO_API MouseButtonEvent : public Event
	{
	public:
		//��ȡ��갴ť
		unsigned int getMouseButton() const { return m_nButtonCode; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		/// @brief Constructor
		/// @param Button 
		MouseButtonEvent(unsigned int Button) 
			: m_nButtonCode(Button) {}

		unsigned int m_nButtonCode;//��갴ť���
	};

	/// @brief ��갴���¼�
	class ECHO_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(unsigned int Button)
			: MouseButtonEvent(Button) {}

		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "MouseButtonPressedEvent: " << m_nButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/// @brief ����ͷ��¼�
	class ECHO_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(unsigned int Button)
			: MouseButtonEvent(Button) {}

		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "MouseButtonReleasedEvent: " << m_nButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}