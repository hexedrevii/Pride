#pragma once

#include <SDL3/SDL.h>

#include "game.h"

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

		/// <summary>
		/// Create a new renderer
		/// </summary>
		bool create(int width, int height);

		/// <summary>
		/// Attaches the renderer for drawing.
		/// </summary>
		void attach();

		/// <summary>
		/// Detaches the renderer without drawing.
		/// </summary>
		void detach();

		/// <summary>
		/// Detaches the renderer and draws it.
		/// </summary>
		void detach_and_draw();

		/// <summary>
		/// Destroys the renderer
		/// </summary>
		void destroy()
		{
			SDL_DestroyTexture(this->m_renderer);
		}
	};
}