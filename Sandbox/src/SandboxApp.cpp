#include <Echo.h>

class ExampleLayer : public Echo::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Echo::Input::IsKeyPressed(ECHO_KEY_TAB))
			ECHO_CLIENT_INFO("Tab Key is pressed!");
	}

	void OnEvent(Echo::Event& event) override
	{
		if (event.GetEventType() == Echo::EventType::KeyPressed)
		{
			Echo::KeyPressedEvent& keyEvent = (Echo::KeyPressedEvent&)event;
			ECHO_CLIENT_TRACE("{0}", (char)keyEvent.getKeyCode());		//输出按下的按键名称
		}
	}

};

class Sandbox : public Echo::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Echo::ImGuiLayer());
	}
	~Sandbox() {}

private:

};

Echo::Application* Echo::CreateApplication()
{
	return new Sandbox;
}