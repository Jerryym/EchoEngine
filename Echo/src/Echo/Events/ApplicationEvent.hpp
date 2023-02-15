#pragma once

#include "Echo/Events/Event.h"

namespace Echo {

	/// @brief 窗口关闭事件
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	
	};

	/// @brief 窗口关闭事件
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(const unsigned int width, const unsigned int height)
			: m_nWidth(width), m_nHeight(height) {}

		unsigned int getWidth() const { return m_nWidth; }
		unsigned int getHeight() const { return m_nHeight; }

		std::string ToString() const override
		{
			std::stringstream ss{};
			ss << "WindowResizeEvent: " << m_nWidth << ", " << m_nHeight;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_nWidth;		//窗口宽
		unsigned int m_nHeight;		//窗口长
	};

	/// @brief AppTick事件
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @brief App更新事件
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @brief App渲染事件
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}