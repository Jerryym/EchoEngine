#pragma once

extern Echo::Application* Echo::CreateApplication();

int main(int argc, char** argv)
{
	//初始化日志系统
	Echo::Log::Init();
	ECHO_CORE_INFO("Initialized Log!");
	ECHO_CLIENT_INFO("Hello, Echo Engine!");

	auto app = Echo::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
