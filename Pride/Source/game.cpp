#include "pride/game.h"

bool Pride::Game::create_window(std::string title, int width, int height)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("ERROR: SDL: Cannot initialise SDL.");
		return false;
	}

	SDL_Log("INFO: SDL: Initialised SDL.");

	this->m_window = SDL_CreateWindow(title.c_str(), width, height, this->m_flags);
	if (!this->m_window)
	{
		SDL_Log("ERROR: SDL: Cannot initialise SDL Window.");
		SDL_Quit();

		return false;
	}

	SDL_Log("INFO: SDL: Initialised SDL Window.");

	this->m_renderer = SDL_CreateRenderer(this->m_window, nullptr);
	if (!this->m_renderer)
	{
		SDL_Log("ERROR: RENDERER: Cannot initialise basic renderer.");

		SDL_DestroyWindow(this->m_window);
		SDL_Quit();
		return false;
	}

	SDL_Log("INFO: RENDERER: Initialised basic renderer.");

	return true;
}

void Pride::Game::poll_events()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_EVENT_QUIT:
			this->m_end = true;
			break;

		default:
			break;
		}
	}
}

void Pride::Game::close_window()
{
	if (this->m_window) SDL_DestroyWindow(this->m_window);
	if (this->m_renderer) SDL_DestroyRenderer(this->m_renderer);

	SDL_Quit();
}