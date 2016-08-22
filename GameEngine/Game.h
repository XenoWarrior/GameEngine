#ifndef Game_H
#define Game_H

#include <string>

#include <windows.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "AssetPipe.h"

#ifdef DrawText
#undef DrawText
#endif;

class Game {
public:
	Game(std::string, int, int);

	bool			InitGame();
	bool			StopGame();
	bool			IsRunning();

	SDL_Window*		GetGameWindow();
	SDL_Renderer*	GetGameRenderer();

	void			SetStartClock();
	void			DrawAll();
	void			HandleInput();

	int				CalculateFPS();

	AssetPipe		asset_pipe = AssetPipe("Assets/");

private:
	SDL_Window*		game_window;
	SDL_Renderer*	game_renderer;

	bool			game_running = false;

	std::string		instance_name;
	int				instance_height;
	int				instance_width;

	Uint32			start_clock = 0;
	Uint32			delta_clock = 0;
	Uint32			current_fps = 0;

	const Uint8*	keyboard_input;

};

#endif
