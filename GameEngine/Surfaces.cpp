#include "Surfaces.h"

Surfaces::Surfaces()
{

}

SDL_Surface * Surfaces::CreateTextSurface(std::string text, TTF_Font * font, SDL_Colour colour)
{
	return TTF_RenderText_Solid(font, text.c_str(), colour);
}
