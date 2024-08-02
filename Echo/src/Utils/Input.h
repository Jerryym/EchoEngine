#pragma once
#include "Core.h"

#include "Utils/MouseCodes.h"
#include "Utils/KeyCodes.h"

namespace Echo {

	class Input
	{
	public:
		/// @brief 键盘是否按下
		/// @param keycode 键盘按键映射
		/// @return 
		static bool IsKeyPressed(Key::KeyCode keycode) { return s_InputInstance->IsKeyPressedImpl(keycode); }
		
		/// @brief 鼠标是否按下
		/// @param mousebutton 鼠标按钮映射
		/// @return 
		static bool IsMouseButtonPressed(Mouse::MouseCode mousebutton) { return s_InputInstance->IsMouseButtonPressedImpl(mousebutton); }

		static std::pair<float, float> GetMousePos() { return s_InputInstance->GetMousePosImpl(); }
		static float GetMouseX() { return s_InputInstance->GetMouseXImpl(); }
		static float GetMouseY() { return s_InputInstance->GetMouseYImpl(); }

	protected:
		/// @brief 键盘按下实现
		/// @param keycode 键盘按键映射
		/// @return 
		virtual bool IsKeyPressedImpl(Key::KeyCode keycode) = 0;

		/// @brief 鼠标按下实现
		/// @param mousebutton 鼠标按钮映射
		/// @return 
		virtual bool IsMouseButtonPressedImpl(Mouse::MouseCode mousebutton) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_InputInstance;
	};

}
