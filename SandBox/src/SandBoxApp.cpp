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
			//ECHO_CLIENT_INFO("ExampleLayer: OnUpdate");
		}

		virtual void OnEvent(Echo::Event& event) override
		{
			//ECHO_CLIENT_INFO("ExampleLayer: OnEvent");
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
