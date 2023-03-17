#pragma once

#include "Echo/Core.h"

namespace Echo {

	class ECHO_API Input
	{
	public:
		/// @brief �����Ƿ���
		/// @param keycode ���̰���ӳ��
		/// @return 
		static bool IsKeyPressed(int keycode) { return s_InputInstance->IsKeyPressedImpl(keycode); }
		
		/// @brief ����Ƿ���
		/// @param mousebutton ��갴ťӳ��
		/// @return 
		static bool IsMouseButtonPressed(int mousebutton) { return s_InputInstance->IsMouseButtonPressedImpl(mousebutton); }

		static std::pair<float, float> GetMousePos() { return s_InputInstance->GetMousePosImpl(); }
		static float GetMouseX() { return s_InputInstance->GetMouseX(); }
		static float GetMouseY() { return s_InputInstance->GetMouseY(); }

	protected:
		/// @brief ���̰���ʵ��
		/// @param keycode ���̰���ӳ��
		/// @return 
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		/// @brief ��갴��ʵ��
		/// @param mousebutton ��갴ťӳ��
		/// @return 
		virtual bool IsMouseButtonPressedImpl(int mousebutton) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_InputInstance;
	};

}