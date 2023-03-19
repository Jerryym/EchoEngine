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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time;
	};

}