#pragma once

#include "Core.h"

namespace Echo {

	class ECHO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


