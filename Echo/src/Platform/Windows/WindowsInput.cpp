#include "echopch.h"
#include "WindowsInput.h"
#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace Echo {

	Input* Input::s_InputInstance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(Key::KeyCode keycode)
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetMainWindow().GetNativeWindow());
		auto state = glfwGetKey(nativeWindow, (int)keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(Mouse::MouseCode mousebutton)
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetMainWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(nativeWindow, (int)mousebutton);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetMainWindow().GetNativeWindow());
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
