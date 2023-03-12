#pragma once

#include "Echo/Layer.h"

#include "Echo/Events/ApplicationEvent.hpp"
#include "Echo/Events/KeyEvent.hpp"
#include "Echo/Events/MouseEvent.hpp"

namespace Echo {

	class ECHO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMousePressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseSrolledEvent(MouseScrolledEvent& event);
		
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		
		bool OnWindowResizedEvent(WindowResizeEvent& event);

	private:
		float m_Time;
	};

}