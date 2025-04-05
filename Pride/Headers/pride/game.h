#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "colour.h"
#include "vec2.h"
#include "content_loader.h"

namespace Pride
{
	struct Event
	{
		SDL_EventType type;
		std::function<void(SDL_Event*)> callback;

		Event(SDL_EventType t, std::function<void(SDL_Event*)> cb) 
            : type(t), callback(cb) {}
	};

	class Game
	{
	private:
		std::vector<Event> m_events;

		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		bool m_end = false;

		SDL_WindowFlags m_flags = 0;
	public:
		// Content manager for the window.
		ContentLoader content = ContentLoader();

		// Set the config flags for the window. Call this BEFORE calling create_window.
		void set_config_flags(SDL_WindowFlags flags)
		{
			this->m_flags = flags;
		}

		// Create the SDL_Window pointer.
		// <param name="name">The window title</param>
		// <returns>Returns true if the window was created successfully, false otherwise</returns>
		bool create_window(std::string name, int width, int height);

		// Create the SDL_Window pointer.
		// <param name="name">The window title</param>
		// <returns>Returns true if the window was created successfully, false otherwise</returns>
		bool create_window(std::string name, Math::Vec2 size);

		// Register a new event for the poll_events function.
		void register_event(SDL_EventType type, std::function<void(SDL_Event*)> callback);

		// Register a new event for the poll_events function.
		void register_event(Event event);

		// Handle window events.
		void poll_events();

		// Destroy window data.
		void close_window();

		// Returns wether window is running or not.
		bool window_should_close() const 
		{
			return this->m_end;
		}

		// Clear the background of the active renderer.
		void clear(const Pride::Colour colour)
		{
			SDL_SetRenderDrawColor(this->m_renderer, colour.r, colour.g, colour.b, colour.a);
			SDL_RenderClear(this->m_renderer);
		}
		
		// Present the current framebuffer and move to the next one.
		void advance_frame()
		{
			SDL_RenderPresent(this->m_renderer);
		}

		// Draw a texture to the screen.
		void draw_texture(SDL_Texture* texture, Math::Vec2 position, Colour tint);

		// Draw a texture to the screen.
		void draw_texture(SDL_Texture* texture, Math::Vec2 position, float scale, Colour tint);

		// Get raw render pointer, shouldn't call this yourself.
		SDL_Renderer* get_raw_renderer() const
		{
			return this->m_renderer;
		}

		// Get raw window pointer, shouldn't call this yourself.
		SDL_Window* get_raw_window() const
		{
			return this->m_window;
		}
	};
}