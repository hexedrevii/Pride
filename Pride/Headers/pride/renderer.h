#pragma once

#include <SDL3/SDL.h>

#include "game.h"
#include "vec2.h"

namespace Pride
{
	/// <summary>
	/// Represents an SDL_Texture
	/// </summary>
	class Renderer
	{
	private:
		SDL_Texture* m_renderer = nullptr;
		SDL_Renderer* m_render;
		SDL_Window* m_window;

		int m_width = 0, m_height = 0;
	public:
		Renderer(Pride::Game* game)
		{
			this->m_render = game->get_raw_renderer();
			this->m_window = game->get_raw_window();
		}

		// Create a new renderer
		bool create(int width, int height);

		// Create a new renderer
		bool create(Math::Vec2 size);

		// Attaches the renderer for drawing.
		void attach();

		// Detaches the renderer without drawing.
		void detach();

		// Detaches the renderer and draws it.
		void detach_and_draw();

		// Destroys the renderer
		void destroy()
		{
			SDL_DestroyTexture(this->m_renderer);
		}
	};
}