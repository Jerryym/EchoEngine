#include <Echo.h>

namespace SandBoxApp {

	class SandBox : public Echo::Application
	{
	public:
		SandBox() {}
		~SandBox() {}
	};

}

Echo::Application* Echo::CreateApplication()
{
	return new SandBoxApp::SandBox;
}
