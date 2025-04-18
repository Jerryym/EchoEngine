#include <Echo.h>

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

}
