#include <Core/Kiwi.h>
#include <Application/Application.h>

void RunApplication()
{
	Ref<Kiwi::Application> application = CreateApplication();

	if (!application->Run())
	{
		RunApplication();
	}
	else
	{
		return;
	}
}

int main(int argc, char* argv[])
{
	KW_LOG("Kiwi version {}.{}", KIWI_VERSION_MAJOR, KIWI_VERSION_MINOR);

#ifdef EXPERIMENTAL_BUILD
	KW_LOG("This is an experimental build of Kiwi. It may be unstable.");
#endif

	RunApplication();

	return 0;
}