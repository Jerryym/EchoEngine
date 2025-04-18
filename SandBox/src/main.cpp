#include "SandBoxApp.h"

int main(int argc, char** argv)
{
	//初始化日志系统
	Echo::Log::Init();
	ECHO_CORE_INFO("Initialized Log!");
	ECHO_CLIENT_INFO("Hello, EchoEngine!");

	//启动应用
	SandBoxApp::SandBox* app = new SandBoxApp::SandBox;
	app->Run();
	delete app;

	return 0;
}
