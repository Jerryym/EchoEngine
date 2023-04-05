#include "echopch.h"
#include "WindowsInput.h"

#include "Echo/Application.h"
#include <GLFW/glfw3.h>

namespace Echo {

	Input* Input::s_InputInstance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(nativeWindow, keycode);

		return state == (GLFW_PRESS | GLFW_REPEAT);
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int mousebutton)
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(nativeWindow, mousebutton);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		double rXPos, rYPos;
		glfwGetCursorPos(nativeWindow, &rXPos, &rYPos);

		return std::pair<float, float>((float)rXPos, (float)rYPos);
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}

}