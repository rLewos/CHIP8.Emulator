#include "Window.h"

Window::Window(std::string title, int width, int height, int win_pos_x, int win_pos_y, Uint32 flags)
{
	m_title = title;
	m_width = width;
	m_height = height;
	m_win_init_position_x = win_pos_x;
	m_win_init_position_y = win_pos_y;
	m_flags = flags;
}

Window::~Window() {
	free();
}

void Window::free()
{
	SDL_DestroyWindow(m_window);
	m_window = nullptr;


	// Check it has some issue.
	SDL_Quit();
}

void Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) == 0)
	{
		m_window = SDL_CreateWindow(m_title.c_str(), m_win_init_position_x, m_win_init_position_y, m_width, m_height, m_flags);
		if (m_window == nullptr)
			throw std::exception(SDL_GetError());
	}
	else {
		throw std::exception("Couldn't initialize SDL.");
	}
}

SDL_Window* Window::getWindow()
{
	return m_window;
}

