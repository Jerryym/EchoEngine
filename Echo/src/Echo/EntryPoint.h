#pragma once

#ifdef ECHO_PLATFORM_WINDOWS

extern Echo::Application* Echo::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Echo::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif // ECHO_PLATFORM_WINDOWS