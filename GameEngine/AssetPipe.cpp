#include "AssetPipe.h"

AssetPipe::AssetPipe(std::string dir)
{
	asset_directory = dir;
	view_port = glm::vec2(0.0f, 0.0f);
}

bool AssetPipe::AddImageAsset(std::string identifier, std::string file)
{
	std::string dir = asset_directory + file;
	asset_surfaces[identifier] = IMG_Load(dir.c_str());
	if (!asset_surfaces[identifier])
	{
		MessageBox(0, IMG_GetError(), "Error", MB_OK);
		asset_surfaces.erase(identifier);
		return false;
	}

	SDL_Rect asset_rect;
	asset_rect.x = 0;
	asset_rect.y = 0;
	asset_rect.w = asset_surfaces[identifier]->w;
	asset_rect.h = asset_surfaces[identifier]->h;
	asset_positions[identifier] = asset_rect;

	return true;
}

bool AssetPipe::AddFontAsset(std::string identifier, std::string file, int size)
{
	std::string dir = asset_directory + file;
	asset_fonts[identifier] = TTF_OpenFont(dir.c_str(), size);
	if (!asset_fonts[identifier])
	{
		MessageBox(0, TTF_GetError(), "Error", MB_OK);
		return false;
	}

	return true;
}

bool AssetPipe::AddTextSurface(std::string identifier, std::string text, std::string font, SDL_Colour colour, glm::vec2 pos)
{
	if (!asset_surfaces_texts[identifier])
	{
		asset_surfaces_texts[identifier] = surface_manager.CreateTextSurface(text, GetAssetFont(font), colour);
		if (!asset_surfaces_texts[identifier])
		{
			MessageBox(0, TTF_GetError(), "Error", MB_OK);
			return false;
		}

		SDL_Rect text_pos;
		text_pos.x = pos.x;
		text_pos.y = pos.y;
		text_pos.w = asset_surfaces_texts[identifier]->w;
		text_pos.h = asset_surfaces_texts[identifier]->h;

		asset_texts_positions[identifier] = text_pos;
	}
	else
	{
		SDL_FreeSurface(asset_surfaces_texts[identifier]);
		asset_surfaces_texts[identifier] = surface_manager.CreateTextSurface(text, GetAssetFont(font), colour);
	}

	return true;
}

SDL_Surface* AssetPipe::GetAssetSurface(std::string identifier)
{
	return asset_surfaces[identifier];
}

SDL_Rect AssetPipe::GetAssetPosition(std::string identifier)
{
	return asset_positions[identifier];
}

TTF_Font* AssetPipe::GetAssetFont(std::string identifier)
{
	return asset_fonts[identifier];
}

SDL_Surface* AssetPipe::GetTextSurface(std::string identifier)
{
	return asset_surfaces_texts[identifier];
}

SDL_Rect AssetPipe::GetTextPosition(std::string identifier)
{
	return asset_texts_positions[identifier];
}

std::map<std::string, SDL_Surface*> AssetPipe::GetTextSurfaces()
{
	return asset_surfaces_texts;
}

std::map<std::string, SDL_Surface*> AssetPipe::GetAllSurfaces()
{
	return asset_surfaces;
}

void AssetPipe::DestroyAll()
{
	for (auto item : asset_surfaces)
	{
		SDL_FreeSurface(item.second);
	}
	asset_surfaces.clear();
	asset_positions.clear();
}

void AssetPipe::AssignPlayerAsset(std::string identifier)
{
	player_asset = identifier;
}

void AssetPipe::MovePlayer(DirectionTypes dir)
{
	if (player_asset != "")
	{
		switch (dir)
		{
			case DIRECTION_UP:
				if(view_port.y != 0.0f & asset_positions[player_asset].y > 1)
				{ 
					asset_positions[player_asset].y -= player_speed;
				}
				break;
			case DIRECTION_DOWN:
				if (view_port.y != 0.0f & asset_positions[player_asset].y < (view_port.y - 32))
				{
					asset_positions[player_asset].y += player_speed;
				}
				break;
			case DIRECTION_LEFT:
				if (view_port.x != 0.0f & asset_positions[player_asset].x > 1)
				{
					asset_positions[player_asset].x -= player_speed;
				}
				break;
			case DIRECTION_RIGHT:
				if (view_port.x != 0.0f & asset_positions[player_asset].x < (view_port.x - 32))
				{
					asset_positions[player_asset].x += player_speed;
				}
				break;
		}
	}
}

std::string AssetPipe::GetPlayerPos()
{
	return glm::to_string(glm::vec2(asset_positions[player_asset].x, asset_positions[player_asset].y));
}

void AssetPipe::SetViewPort(int h, int w)
{
	view_port = glm::vec2(h, w);
}