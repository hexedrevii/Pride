#pragma once

#include <SDL3/SDL.h>

#include "game.h"
#include "vec2.h"

namespace Pride
{
    /**
     * @brief Represents an SDL_Texture wrapper for rendering operations.
     * @details Manages texture creation, attachment, and destruction.
     */
    class Renderer
    {
    public:
        /**
         * @brief Constructs a Renderer tied to a Game instance.
         * @param game Pointer to the parent Pride::Game object.
         */
        Renderer(Pride::Game* game)
        {
            this->m_render = game->get_raw_renderer();
            this->m_window = game->get_raw_window();
        }

        /**
         * @brief Creates a new renderer texture with specified dimensions.
         * @param width Texture width in pixels.
         * @param height Texture height in pixels.
         * @return true if creation succeeded, false on error.
         */
        bool create(int width, int height);

        /**
         * @brief Creates a new renderer texture (Vec2 overload).
         * @param size Texture dimensions as Math::Vec2.
         * @return true if creation succeeded, false on error.
         */
        bool create(Math::Vec2 size);

        /**
         * @brief Binds the renderer as the current drawing target.
         * @note All subsequent draw operations will affect this texture.
         */
        void attach();

        /**
         * @brief Unbinds the renderer without presenting changes.
         * @warning Leaves drawn content in an undefined state until reattached.
         */
        void detach();

        /**
         * @brief Unbinds the renderer and flushes all pending draw commands.
         * @details Equivalent to detach() + immediate GPU submission.
         */
        void detach_and_draw();

        /**
         * @brief Destroys the renderer and releases SDL resources.
         * @warning The object becomes unusable after this call.
         */
        void destroy()
        {
            SDL_DestroyTexture(this->m_renderer);
        }
    private:
        SDL_Texture* m_renderer = nullptr;
        SDL_Renderer* m_render;
        SDL_Window* m_window;
        int m_width = 0;
        int m_height = 0;
    };
}
