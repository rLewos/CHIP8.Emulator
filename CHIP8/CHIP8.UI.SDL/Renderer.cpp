#include "Renderer.h"

Renderer::Renderer(Window* window)
{
	m_window = window;
}

Renderer::~Renderer()
{
	free();
}

void Renderer::init()
{
	m_renderer = SDL_CreateRenderer(m_window->getWindow(), 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
		throw std::exception(SDL_GetError());
}

void Renderer::free()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}