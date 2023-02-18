#pragma once

#include "Echo/Events/Event.h"

namespace Echo {

	/// @brief ���ڹر��¼�
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	
	};

	/// @brief ���ڹر��¼�
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
		unsigned int m_nWidth;		//���ڿ�
		unsigned int m_nHeight;		//���ڳ�
	};

	/// @brief AppTick�¼�
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @brief App�����¼�
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @brief App��Ⱦ�¼�
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}