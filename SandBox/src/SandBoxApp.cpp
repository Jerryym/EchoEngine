#include <Echo.h>

namespace SandBoxApp {

	class ExampleLayer : public Echo::Layer
	{
	public:
		ExampleLayer()
			: Echo::Layer("Example")
		{}

	public:
		virtual void OnUpdate() override
		{
			if (Echo::Input::IsKeyPressed(ECHO_KEY_TAB))
				ECHO_CLIENT_INFO("Tab Key is pressed!");
		}

		virtual void OnEvent(Echo::Event& event) override
		{
			if (event.GetEventType() == Echo::EventType::KeyPressed)
			{
				Echo::KeyPressedEvent& keyEvent = (Echo::KeyPressedEvent&)event;
				ECHO_CLIENT_TRACE("{0}", (char)keyEvent.getKeyCode());		//输出按下的按键名称
			}
		}
	};

	class SandBox : public Echo::Application
	{
	public:
		SandBox() 
		{
			Echo::Application::PushLayer(new ExampleLayer);
		}

		~SandBox() {}
	};

}

Echo::Application* Echo::CreateApplication()
{
	return new SandBoxApp::SandBox;
}
