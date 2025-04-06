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

	if (!this->drawables.create(this->m_renderer))
	{
		return false;
	}

	SDL_Log("INFO: DRAWABLE: Created drawable.");

	if (!this->content.load_renderer(this->m_renderer))
	{
		SDL_Log("ERROR: CONTENT_LOADER: Failed to load renderer, it does not exist.");
		return false;
	}

	SDL_Log("INFO: CONTENT_LOADER: Created content loader.");

	return true;
}

bool Pride::Game::create_window(std::string title, Pride::Math::Vec2 size)
{
	return this->create_window(title, size.x, size.y);
}

void Pride::Game::poll_events()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT)
		{
			this->m_end = true;
		}

		for (const Event& bound_event : this->m_events)
		{
			if (e.type == bound_event.type)
			{
				bound_event.callback(&e);
			}
		}
	}
}

void Pride::Game::register_event(Pride::Event event)
{
	this->m_events.push_back(event);
}

void Pride::Game::register_event(SDL_EventType type, std::function<void(SDL_Event*)> callback)
{
	this->m_events.push_back(Pride::Event(type, callback));
}

void Pride::Game::close_window()
{
	if (this->m_window)
	{
		SDL_DestroyWindow(this->m_window);
		SDL_Log("INFO: SDL: Destroyed window pointer.");
	}

	if (this->m_renderer)
	{
		SDL_DestroyRenderer(this->m_renderer);
		SDL_Log("INFO: SDL: Destroyed render pointer.");
	}

	SDL_Log("INFO: SDL: Quitting SDL.");
	SDL_Quit();
}