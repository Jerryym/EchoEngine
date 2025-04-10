#include <Echo.h>
#include "Core/EntryPoint.h"

#include "ExampleLayer.h"

namespace SandBoxApp {
	
	class SandBox : public Echo::Application 
	{
	public:
		SandBox()
		{
			Echo::Application::PushLayer(new ExampeleLayer);
		}
		~SandBox() = default;
	};

} // namespace SandBoxApp

Echo::Application* Echo::CreateApplication()
{
	return new SandBoxApp::SandBox;
}
