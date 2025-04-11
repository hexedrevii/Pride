#pragma once

#include <SDL3/SDL.h>

#include "vec2.h"
#include "colour.h"

namespace Pride
{
    class Drawable
    {
    public:
        /// @brief Create the Drawable.
        bool create(SDL_Renderer* render)
        {
            if (!render)
            {
                SDL_Log("ERROR: DRAWABLE: Renderer isn't created.");
                return false;
            }

            this->m_renderer = render;
            return true;
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
    private:
        SDL_Renderer* m_renderer = nullptr;
    };
}
