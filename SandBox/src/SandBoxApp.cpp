#include <Nest.h>
#include <Engine.h>

class SandBox : public Nest::Application
{
public:
	SandBox(int& argc, char** argv)
		: Application(argc, argv)
	{

	}
	~SandBox() {}

private:

};

Nest::Application* Nest::CreateApplication(int argc, char** argv)
{
	return new SandBox(argc, argv);
}
