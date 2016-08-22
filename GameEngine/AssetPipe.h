#ifndef AssetPipe_H
#define AssetPipe_H

#include <string>
#include <map>

#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "AppCommon.h"
#include "Surfaces.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtx\string_cast.hpp"

class AssetPipe {
public:
	AssetPipe(std::string);

	bool									AddImageAsset(std::string, std::string);
	bool									AddFontAsset(std::string, std::string, int);
	bool									AddTextSurface(std::string, std::string, std::string, SDL_Colour, glm::vec2);

	SDL_Surface*							GetAssetSurface(std::string);
	SDL_Rect								GetAssetPosition(std::string);
	TTF_Font*								GetAssetFont(std::string);

	SDL_Surface*							GetTextSurface(std::string);
	SDL_Rect								GetTextPosition(std::string);

	std::map<std::string, SDL_Surface*>		GetTextSurfaces();
	std::map<std::string, SDL_Surface*>		GetAllSurfaces();

	void									DestroyAll();
	void									AssignPlayerAsset(std::string);
	void									MovePlayer(DirectionTypes);
	std::string								GetPlayerPos();
	void									SetViewPort(int, int);

private:
	Surfaces								surface_manager;

	std::map<std::string, SDL_Surface*>		asset_surfaces;
	std::map<std::string, TTF_Font*>		asset_fonts;
	std::map<std::string, SDL_Rect>			asset_positions;
	std::map<std::string, SDL_Surface*>		asset_surfaces_texts;
	std::map<std::string, SDL_Rect>			asset_texts_positions;

	std::string								asset_directory;
	std::string								player_asset;

	glm::vec2								view_port;

	int										player_speed = 2;

};

#endif

