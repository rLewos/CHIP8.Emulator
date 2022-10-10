#include <iostream>
#include <SDL.h>
#include "../CHIP8/CPU.h"


int main(int argc, char* argv[])
{
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	SDL_Texture* screen{ nullptr };
	SDL_Surface* surfaceScreen{ nullptr };

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

			surfaceScreen = SDL_CreateRGBSurface(0, 64, 32, 32, 0x0, 0x0, 0x0, 0x0);
			screen = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_STREAMING, 64, 32);
			void* pixels = nullptr;
			int pitch = 0;

			SDL_LockTexture(screen, nullptr, &pixels, &pitch);
			std::memcpy(pixels, surfaceScreen->pixels, surfaceScreen->w * surfaceScreen->h);
			SDL_UnlockTexture(screen);

			int32_t numeroPixels = (surfaceScreen->pitch / 4) * 64;
			uint32_t* intPixels = (uint32_t*)pixels;

			CPU cpu;
			cpu.loadCartridge("E:\\Roms\\Chip8\\test_opcode.ch8");

			while (!quit)
			{
				while (SDL_PollEvent(&e)) {
					switch (e.type)
					{
						case SDL_QUIT:
							quit = true;
							break;
						
						default:
							break;
					}
				}

				cpu.runCicle();
				if (cpu.getHasDrawn())
				{
					SDL_LockTexture(screen, nullptr, &pixels, &pitch);

					std::array <std::array<uint8_t, 32>, 64 > tela = cpu.getScreen();

					for (size_t y = 0; y < 32; y++)
					{
						for (size_t x = 0; x < 64; x++)
						{
							uint8_t pixelByte = tela[x][y];
							if (pixelByte != 0x0)
								intPixels[y * 64 + x] = 0xFFFFFFFF;
						}
					}

					SDL_UnlockTexture(screen);

					SDL_UpdateTexture(screen, nullptr, pixels, pitch);
					SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);
					SDL_RenderCopy(renderer, screen, nullptr, nullptr);
					SDL_RenderPresent(renderer);
				}

			}
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

	SDL_DestroyTexture(screen);
	screen = nullptr;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	SDL_Quit();

    return 0;
}