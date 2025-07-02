#include <Core/Kiwi.h>

int main(int argc, char* argv[])
{
	KW_LOG("Kiwi version " << KIWI_VERSION_MAJOR << "." << KIWI_VERSION_MINOR << " initialising.");

#ifdef EXPERIMENTAL_BUILD
	KW_LOG("This is an experimental build of Kiwi. It may be unstable.");
#endif
	
	return 0;
}