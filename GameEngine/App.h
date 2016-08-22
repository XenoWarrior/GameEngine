#ifndef App_H
#define App_H

#include <memory>
#include <string>

#include <windows.h>

#include "Game.h"
#include "AssetPipe.h"
#include "Surfaces.h"
#include "AppCommon.h"

#include "glm/glm/glm.hpp"

class App{
public:
	App();

	bool		Run();

private:
	SDL_Event	event;

	Game		game_instance = Game("XenEngine Instance", 640, 480);

};

#endif