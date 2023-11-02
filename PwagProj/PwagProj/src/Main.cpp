#include <Application/Application.h>

int main()
{
	Application::Create();
	Application::Get()->Run();
	Application::Destroy();
	return 0;
}
