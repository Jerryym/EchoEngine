#pragma once

#include "Echo/Events/Event.h"

// 鼠标事件
namespace Echo {

	/// @brief 鼠标移动事件
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			: m_PositionX(x), m_PositionY(y) {}

		float getX() const { return m_PositionX; }
		float getY() const { return m_PositionY; }

		std::string ToString() const override
		{
			// 使用 std::stringstream 实现数据类型转换
			std::stringstream ss{};
			ss << "MouseMovedEvent: " << m_PositionX << ", " << m_PositionY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private: 
		float m_PositionX;
		float m_PositionY;
	};

	/// @brief 鼠标滚动事件
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float x, const float y)
			: m_XOffset(x), m_YOffset(y) {}

		float getXOffset() const { return m_XOffset; }
		float getYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			// 使用 std::stringstream 实现数据类型转换
			std::stringstream ss{};
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset;	// x轴偏移
		float m_YOffset;	// y轴偏移
	};

	/// @brief 鼠标按钮事件
	class MouseButtonEvent : public Event
	{
	public:
		//获取鼠标按钮
		unsigned int getMouseButton() const { return m_ButtonCode; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		/// @brief Constructor
		/// @param Button 
		MouseButtonEvent(const unsigned int Button) 
			: m_ButtonCode(Button) {}

		unsigned int m_ButtonCode;//鼠标按钮编号
	};

	/// @brief 鼠标按下事件
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const unsigned int Button)
			: MouseButtonEvent(Button) {}

		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "MouseButtonPressedEvent: " << m_ButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/// @brief 鼠标按下事件
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const unsigned int Button)
			: MouseButtonEvent(Button) {}

		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "MouseButtonReleasedEvent: " << m_ButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}