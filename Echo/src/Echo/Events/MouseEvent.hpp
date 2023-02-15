#pragma once

#include "Echo/Events/Event.h"

// 鼠标事件
namespace Echo {

	/// @brief 鼠标移动事件
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			: m_rPositionX(x), m_rPositionY(y) {}

		float getX() const { return m_rPositionX; }
		float getY() const { return m_rPositionY; }

		std::string ToString() const override
		{
			// 使用 std::stringstream 实现数据类型转换
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

	/// @brief 鼠标滚动事件
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float x, const float y)
			: m_rOffsetX(x), m_rOffsetY(y) {}

		float getXOffset() const { return m_rOffsetX; }
		float getYOffset() const { return m_rOffsetY; }

		std::string ToString() const override
		{
			// 使用 std::stringstream 实现数据类型转换
			std::stringstream ss{};
			ss << "MouseScrolledEvent: " << m_rOffsetX << ", " << m_rOffsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_rOffsetX;	// x轴偏移
		float m_rOffsetY;	// y轴偏移
	};

	/// @brief 鼠标按钮事件
	class MouseButtonEvent : public Event
	{
	public:
		//获取鼠标按钮
		unsigned int getMouseButton() const { return m_nButtonCode; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		/// @brief Constructor
		/// @param Button 
		MouseButtonEvent(const unsigned int Button) 
			: m_nButtonCode(Button) {}

		unsigned int m_nButtonCode;//鼠标按钮编号
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
			ss << "MouseButtonPressedEvent: " << m_nButtonCode;
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
			ss << "MouseButtonReleasedEvent: " << m_nButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}