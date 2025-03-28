#pragma once

#include <SDL3/SDL.h>

#include <string>

#include "colour.h"

namespace Pride
{
	class Game
	{
	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		bool m_end = false;

		SDL_WindowFlags m_flags = 0;
	public:
		void set_config_flags(SDL_WindowFlags flags)
		{
			this->m_flags = flags;
		}

		bool create_window(std::string name, int width, int height);
		void poll_events();
		void close_window();

		bool window_should_close() const 
		{
			return this->m_end;
		}

		void clear(Pride::Colour colour)
		{
			SDL_SetRenderDrawColor(this->m_renderer, colour.r, colour.g, colour.b, colour.a);
			SDL_RenderClear(this->m_renderer);
		}
		
		void advance_frame()
		{
			SDL_RenderPresent(this->m_renderer);
		}

		SDL_Renderer* get_raw_renderer() const
		{
			return this->m_renderer;
		}

		SDL_Window* get_raw_window() const
		{
			return this->m_window;
		}
	};
}