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
		ECHO_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Echo::Event& event) override
	{
		ECHO_CLIENT_TRACE("{0}", event);
	}

};

class Sandbox : public Echo::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}

private:

};

Echo::Application* Echo::CreateApplication()
{
	return new Sandbox;
}