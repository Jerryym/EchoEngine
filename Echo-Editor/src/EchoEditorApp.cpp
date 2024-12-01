#include <Echo.h>
#include "Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Echo {

	class EchoEditor : public Application
	{
	public:
		EchoEditor() 
			: Application("Echo Editor")
		{
			Application::PushLayer(new EditorLayer);
		}

		~EchoEditor() {}
	};

	Application* CreateApplication()
	{
		return new EchoEditor;
	}

}
