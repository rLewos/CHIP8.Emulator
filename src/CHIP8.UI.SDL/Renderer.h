#include <SDL.h>
#include "Window.h"

class Renderer
{
private:
	SDL_Renderer* m_renderer;
	Window* m_window;
	void free();

public:
	Renderer(Window* window);
	~Renderer();
	void init();
};

