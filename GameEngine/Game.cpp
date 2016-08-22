#include "Game.h"

Game::Game(std::string caption, int height, int width)
{
	instance_name = caption;
	instance_height = height;
	instance_width = width;
}

bool Game::InitGame()
{
	 if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	 {
		 MessageBox(0, SDL_GetError(), "Error", MB_OK);
		 return false;
	 }
	 if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
	 {
		 MessageBox(0, IMG_GetError(), "Error", MB_OK);
		 return false;
	 }
	 if (TTF_Init() < 0)
	 {
		 MessageBox(0, TTF_GetError(), "Error", MB_OK);
		 return false;
	 }

	 game_window = SDL_CreateWindow(instance_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, instance_height, instance_width, 0);
	 game_renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	 if (!game_window | !game_renderer)
	 {
		 return false;
	 }

	 game_running = true;
	 return true;
}

bool Game::StopGame()
{
	SDL_DestroyRenderer(game_renderer);
	SDL_DestroyWindow(game_window);

	game_running = false;

	SDL_Quit();
	IMG_Quit();

	return true;
}

bool Game::IsRunning()
{
	return game_running;
}

SDL_Window* Game::GetGameWindow()
{
	return game_window;
}

SDL_Renderer* Game::GetGameRenderer()
{
	return game_renderer;
}

void Game::DrawAll()
{
	SDL_Texture* item_texture;

	SDL_RenderClear(GetGameRenderer());
	for (auto item : asset_pipe.GetAllSurfaces())
	{
		item_texture = SDL_CreateTextureFromSurface(GetGameRenderer(), item.second);
		SDL_RenderCopy(GetGameRenderer(), item_texture, NULL, &asset_pipe.GetAssetPosition(item.first));
		SDL_DestroyTexture(item_texture);
	}

	for (auto item : asset_pipe.GetTextSurfaces())
	{
		item_texture = SDL_CreateTextureFromSurface(GetGameRenderer(), item.second);
		SDL_RenderCopy(GetGameRenderer(), item_texture, NULL, &asset_pipe.GetTextPosition(item.first));
		SDL_DestroyTexture(item_texture);
	}
	SDL_RenderPresent(GetGameRenderer());
}

void Game::SetStartClock()
{
	start_clock = SDL_GetTicks();
}

int Game::CalculateFPS()
{
	delta_clock = SDL_GetTicks() - start_clock;
	start_clock = SDL_GetTicks();
	if (delta_clock != 0)
	{
		current_fps = 1000 / delta_clock;
	}

	return current_fps;
}

void Game::HandleInput()
{
	keyboard_input = SDL_GetKeyboardState(NULL);
	if (keyboard_input[SDL_SCANCODE_ESCAPE])
	{
		StopGame();
	}

	if (keyboard_input[SDL_SCANCODE_W])
	{
		asset_pipe.MovePlayer(DIRECTION_UP);
	}
	if (keyboard_input[SDL_SCANCODE_A])
	{
		asset_pipe.MovePlayer(DIRECTION_LEFT);
	}
	if (keyboard_input[SDL_SCANCODE_S])
	{
		asset_pipe.MovePlayer(DIRECTION_DOWN);
	}
	if (keyboard_input[SDL_SCANCODE_D])
	{
		asset_pipe.MovePlayer(DIRECTION_RIGHT);
	}
}