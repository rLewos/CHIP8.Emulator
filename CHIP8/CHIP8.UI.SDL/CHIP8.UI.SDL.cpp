#include <iostream>
#include <SDL.h>

int main(int argc, char* argv[])
{
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) == 0)
		{
			window = SDL_CreateWindow("CHIP8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
			if (window == nullptr)
				throw std::exception("Can't create window");

			renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr)
				throw std::exception("Can't create renderer");

			bool quit = false;
			SDL_Event e;


		}
		else 
		{
			throw std::exception("SDL can't be initialized!");
		}
	}
	catch (const std::exception& e)
	{
		printf("%s: %s", e.what(), SDL_GetError());
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	SDL_Quit();

    return 0;
}