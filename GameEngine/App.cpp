#include "App.h"

App::App()
{

}

bool App::Run()
{
	if (!game_instance.InitGame())
	{
		MessageBox(0, "Unable to initialise game instance", "Error", MB_OK);
		game_instance.StopGame();
		return 0;
	}
	if (!game_instance.asset_pipe.AddImageAsset("Player", "Sprites/Player.png"))
	{
		MessageBox(0, "Unable to load game sprite assets", "Error", MB_OK);
		game_instance.StopGame();
		return 0;
	}
	if (!game_instance.asset_pipe.AddFontAsset("ConsoleFont", "Fonts/ConsoleFont.ttf", 24))
	{
		MessageBox(0, "Unable to load game font assets", "Error", MB_OK);
		game_instance.StopGame();
		return 0;
	}
	if (!game_instance.asset_pipe.AddFontAsset("FreeSans", "Fonts/FreeSans.ttf", 16))
	{
		MessageBox(0, "Unable to load game font assets", "Error", MB_OK);
		game_instance.StopGame();
		return 0;
	}

	game_instance.asset_pipe.AssignPlayerAsset("Player");
	game_instance.asset_pipe.SetViewPort(640, 480);
	game_instance.asset_pipe.AddTextSurface("Phrase_Game_Engine", "XenEngine v0.1 (c) XenPowered 2016", "FreeSans", SDL_Color{ 255,255,255 }, glm::vec2(10, 10));
	game_instance.SetStartClock();

	while (game_instance.IsRunning())
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					game_instance.StopGame();
					break;
				default:
					break;
			}
		}

		game_instance.asset_pipe.AddTextSurface("Phrase_FPS_Count",  "FPS: " + std::to_string(game_instance.CalculateFPS()), "FreeSans", SDL_Colour{ 255,255,255 }, glm::vec2(10, 460));
		game_instance.asset_pipe.AddTextSurface("Phrase_Player_Pos", "Player Position: " + game_instance.asset_pipe.GetPlayerPos(), "FreeSans", SDL_Colour{ 255,255,255 }, glm::vec2(10, 26));
		game_instance.DrawAll();
		game_instance.HandleInput();
	}

	return 0;
}
