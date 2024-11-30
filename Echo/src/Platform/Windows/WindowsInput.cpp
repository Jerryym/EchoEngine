#include "echopch.h"
#include "Utils/Input.h"
#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace Echo {

	bool Input::IsKeyPressed(Key::KeyCode keycode)
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetMainWindow().GetNativeWindow());
		auto state = glfwGetKey(nativeWindow, (int)keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(Mouse::MouseCode mousebutton)
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetMainWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(nativeWindow, (int)mousebutton);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		auto nativeWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetMainWindow().GetNativeWindow());
		double rXPos, rYPos;
		glfwGetCursorPos(nativeWindow, &rXPos, &rYPos);

		return std::pair<float, float>((float)rXPos, (float)rYPos);
	}

	float Input::GetMouseX()
	{
		auto[x, y] = GetMousePos();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePos();
		return y;
	}

}
