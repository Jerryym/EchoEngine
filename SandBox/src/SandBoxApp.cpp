#include <Echo.h>
#include "Core/EntryPoint.h"

#include "SandBox2D.h"

namespace SandBoxApp {

	class SandBox : public Echo::Application
	{
	public:
		SandBox() 
		{
			Echo::Application::PushLayer(new SandBox2D);
		}

		~SandBox() {}
	};

}

Echo::Application* Echo::CreateApplication()
{
	return new SandBoxApp::SandBox;
}
