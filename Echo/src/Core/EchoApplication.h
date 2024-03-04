#pragma once
#include "EngineCore.h"
#include <Nest.h>
#include "GUI/Windows_MainWindow.h"

namespace Echo {

	class ECHO_API EchoApplication : public Nest::Application
	{
		Q_OBJECT
	public:
		EchoApplication(int& argc, char** argv);
		virtual ~EchoApplication() {}

	};

	// To be defined in CLIENT
	EchoApplication* CreateApplication(int argc, char** argv);
}

