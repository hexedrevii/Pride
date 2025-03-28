#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <string>
#include <memory>

#include "colour.h"
#include "vec2.h"
#include "content_loader.h"

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
		/// <summary>
		/// Content manager for the window.
		/// </summary>
		ContentLoader content = ContentLoader();

		/// <summary>
		/// Set the config flags for the window. Call this BEFORE calling create_window.
		/// </summary>
		void set_config_flags(SDL_WindowFlags flags)
		{
			this->m_flags = flags;
		}

		/// <summary>
		/// Create the SDL_Window pointer.
		/// </summary>
		/// <param name="name">The window title</param>
		/// <returns>Returns true if the window was created successfully, false otherwise</returns>
		bool create_window(std::string name, int width, int height);

		/// <summary>
		/// Create the SDL_Window pointer.
		/// </summary>
		/// <param name="name">The window title</param>
		/// <returns>Returns true if the window was created successfully, false otherwise</returns>
		bool create_window(std::string name, Math::Vec2 size);

		/// <summary>
		/// Handle window events.
		/// </summary>
		void poll_events();

		/// <summary>
		/// Destroy window data.
		/// </summary>
		void close_window();

		/// <summary>
		/// Returns wether window is running or not.
		/// </summary>
		bool window_should_close() const 
		{
			return this->m_end;
		}

		/// <summary>
		/// Clear the background of the active renderer.
		/// </summary>
		void clear(const Pride::Colour colour)
		{
			SDL_SetRenderDrawColor(this->m_renderer, colour.r, colour.g, colour.b, colour.a);
			SDL_RenderClear(this->m_renderer);
		}
		
		/// <summary>
		/// Present the current framebuffer and move to the next one.
		/// </summary>
		void advance_frame()
		{
			SDL_RenderPresent(this->m_renderer);
		}

		/// <summary>
		/// Draw a texture to the screen.
		/// </summary>
		void draw_texture(SDL_Texture* texture, Math::Vec2 position, Colour tint);

		/// <summary>
		/// Draw a texture to the screen.
		/// </summary>
		void draw_texture(SDL_Texture* texture, Math::Vec2 position, float scale, Colour tint);

		/// <summary>
		/// Get raw render pointer, shouldn't call this yourself.
		/// </summary>
		SDL_Renderer* get_raw_renderer() const
		{
			return this->m_renderer;
		}

		/// <summary>
		/// Get raw window pointer, shouldn't call this yourself.
		/// </summary>
		SDL_Window* get_raw_window() const
		{
			return this->m_window;
		}
	};
}