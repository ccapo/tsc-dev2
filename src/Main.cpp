#include "Main.hpp"

TCODRandom *rng = TCODRandom::getInstance();
Engine *engine = new Engine();

int main()
{
	engine->Startup();

	while( engine->status && !TCODConsole::isWindowClosed() )
	{
		engine->Update();
		engine->Render();
		TCODConsole::flush();
	}

	engine->Shutdown();

	return 0;
}
