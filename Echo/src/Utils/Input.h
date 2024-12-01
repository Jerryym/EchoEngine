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
		static bool IsKeyPressed(Key::KeyCode keycode);
		
		/// @brief 鼠标是否按下
		/// @param mousebutton 鼠标按钮映射
		/// @return 
		static bool IsMouseButtonPressed(Mouse::MouseCode mousebutton);

		static std::pair<float, float> GetMousePos();
		static float GetMouseX();
		static float GetMouseY();
	};

}
