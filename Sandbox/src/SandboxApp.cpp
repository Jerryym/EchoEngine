#include <Echo.h>

class Sandbox : public Echo::Application
{
public:
	Sandbox() {}
	~Sandbox() {}

private:

};

Echo::Application* Echo::CreateApplication()
{
	return new Sandbox;
}