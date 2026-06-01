#include "pch.h"
#include <ctime>
#include "Game.h"


void StartHeapControl();
void DumpMemoryLeaks();

int SDL_main(int argv, char** args)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	StartHeapControl();

	const float width{ 256 };
	//const float height{ 423 };
	const float height{ 200 };
	const float scale{ 3.f };
	//Game* pGame{ new Game{ Window{ "Project name - Name, first name - 1DAEXX", 512.f * 1.5f , 400.f * 1.5f } } };
	Game* pGame{new Game{ Window{ "Pokemon pinball ruby and saphire - Vannieuwkerke, Alexander - 1DAE13", width*scale , height*scale }, scale } };
	pGame->Run();
	delete pGame;

	DumpMemoryLeaks();
	return 0;
}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}


