#include "controller/engine.h"
#include <crtdbg.h>

int main() {
	Engine().run();
	_CrtDumpMemoryLeaks();
	return 0;
}