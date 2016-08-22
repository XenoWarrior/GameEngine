#ifndef Surfaces_H
#define Surfaces_H

#include <string>

#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Surfaces.h"

class Surfaces{
public:
	Surfaces();

	SDL_Surface*	CreateTextSurface(std::string, TTF_Font*, SDL_Colour);

private:

};

#endif;
