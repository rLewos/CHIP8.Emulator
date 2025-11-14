#include <string>
#include <SDL.h>

class Window
{
private:
	SDL_Window* m_window{ nullptr };
	std::string m_title;
	int m_width;
	int m_height;
	int m_win_init_position_x;
	int m_win_init_position_y;
	Uint32 m_flags;

	void free();

public:
	Window(std::string title, int width, int height, int win_pos_x, int win_pos_y, Uint32 flags);
	~Window();

	void init();
	SDL_Window* getWindow();
};

