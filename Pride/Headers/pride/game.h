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
		/// @brief Content manager for the window.
		ContentLoader content = ContentLoader();
	
		/**
		 * @brief Set the config flags for the window. 
		 * @note Call this BEFORE calling create_window().
		 * @param flags SDL_WindowFlags to configure window behavior.
		 */
		void set_config_flags(SDL_WindowFlags flags)
		{
			this->m_flags = flags;
		}
	
		/**
		 * @brief Creates the SDL_Window pointer.
		 * @param name The window title.
		 * @param width The window width in pixels.
		 * @param height The window height in pixels.
		 * @return true if the window was created successfully, false otherwise.
		 */
		bool create_window(std::string name, int width, int height);
	
		/**
		 * @brief Creates the SDL_Window pointer (Vec2 overload).
		 * @param name The window title.
		 * @param size Window dimensions (width and height) as a Vec2.
		 * @return true if the window was created successfully, false otherwise.
		 */
		bool create_window(std::string name, Math::Vec2 size);
	
		/**
		 * @brief Register a new event callback for poll_events().
		 * @param type The SDL_EventType to listen for (e.g., SDL_KEYDOWN).
		 * @param callback Function to execute when the event occurs.
		 */
		void register_event(SDL_EventType type, std::function<void(SDL_Event*)> callback);
	
		/**
		 * @brief Register a pre-configured Event object for poll_events().
		 * @param event The Event struct containing type and callback.
		 */
		void register_event(Event event);
	
		/// @brief Process all pending window events (call once per frame).
		void poll_events();
	
		/// @brief Safely destroy the window and cleanup resources.
		void close_window();
	
		/**
		 * @brief Check if the window should close (e.g., after SDL_QUIT).
		 * @return true if the window is flagged to close, false otherwise.
		 */
		bool window_should_close() const 
		{
			return this->m_end;
		}
	
		/**
		 * @brief Clear the renderer with a solid colour.
		 * @param colour The background colour (Pride::Colour RGBA format).
		 */
		void clear(const Pride::Colour colour)
		{
			SDL_SetRenderDrawColor(this->m_renderer, colour.r, colour.g, colour.b, colour.a);
			SDL_RenderClear(this->m_renderer);
		}
		
		/// @brief Present the rendered frame and prepare for the next one.
		void advance_frame()
		{
			SDL_RenderPresent(this->m_renderer);
		}
	
		/**
		 * @brief Draw a texture at a specific position.
		 * @param texture The SDL_Texture to render.
		 * @param position Screen coordinates (Vec2).
		 * @param tint Colour modulation (Pride::Colour).
		 */
		void draw_texture(SDL_Texture* texture, Math::Vec2 position, Colour tint);
	
		/**
		 * @brief Draw a scaled texture at a position.
		 * @param texture The SDL_Texture to render.
		 * @param position Screen coordinates (Vec2).
		 * @param scale Multiplier for texture size.
		 * @param tint Colour modulation (Pride::Colour).
		 */
		void draw_texture(SDL_Texture* texture, Math::Vec2 position, float scale, Colour tint);
	
		/**
		 * @brief Get the internal SDL_Renderer (advanced use only).
		 * @warning Avoid direct manipulation unless necessary.
		 * @return Raw SDL_Renderer pointer.
		 */
		SDL_Renderer* get_raw_renderer() const
		{
			return this->m_renderer;
		}
	
		/**
		 * @brief Get the internal SDL_Window (advanced use only).
		 * @warning Avoid direct manipulation unless necessary.
		 * @return Raw SDL_Window pointer.
		 */
		SDL_Window* get_raw_window() const
		{
			return this->m_window;
		}
	};
}