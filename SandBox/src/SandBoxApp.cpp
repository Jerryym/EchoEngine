#include <Echo.h>
#include "Core/EntryPoint.h"

namespace SandBoxApp {
	
	class SandBox : public Echo::Application 
	{
	public:
		SandBox() {}
		~SandBox() = default;
	};

} // namespace SandBoxApp

Echo::Application* Echo::CreateApplication()
{
	return new SandBoxApp::SandBox;
}
