#include <Nest.h>
#include <Engine.h>

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
