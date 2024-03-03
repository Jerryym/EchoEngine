#include <Nest.h>
#include <Echo.h>

class ExampleLayer : public Echo::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	virtual void OnUpdate() override
	{
		
	}

};

class SandBox : public Echo::EchoApplication
{
public:
	SandBox(int& argc, char** argv)
		: Echo::EchoApplication(argc, argv)
	{

	}
	~SandBox() {}

private:

};

Echo::EchoApplication* Echo::CreateApplication(int argc, char** argv)
{
	return new SandBox(argc, argv);
}
