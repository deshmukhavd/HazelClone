#include "hzpch.h"
#include "WindowsInput.h"
#include "Hazel/Application.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool status = glfwGetKey(window, keyCode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;	
	};

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool status = glfwGetMouseButton(window, button);
		return status == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}
	float WindowsInput::GetMouseXImpl()
	{
		/*std::pair<float, float> pos = GetMousePositionImpl();
		return pos.first;*/
		/*auto[x, y] = GetMousePositionImpl();
		return x;*/
		auto v = GetMousePositionImpl();
		return std::get<0>(v);
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto v = GetMousePositionImpl();
		return std::get<1>(v);
	}
}