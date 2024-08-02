#pragma once

#include"Utils/Input.h"

namespace Echo {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(Key::KeyCode keycode) override;

		virtual bool IsMouseButtonPressedImpl(Mouse::MouseCode mousebutton) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}

