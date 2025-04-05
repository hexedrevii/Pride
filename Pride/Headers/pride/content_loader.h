#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <filesystem>
#include <string>

namespace Pride
{
    /**
     * @brief Handles loading and management of game assets (textures, etc.).
     * @details Requires an initialized SDL_Renderer before use.
     */
    class ContentLoader
    {
    private:
        SDL_Renderer* m_renderer = nullptr;

    public:
        /**
         * @brief Initializes the content loader with a renderer.
         * @param renderer Valid SDL_Renderer pointer (must not be null).
         * @return true if renderer was set successfully, false if input was null.
         * @warning Calling asset methods before this succeeds will cause crashes.
         */
        bool load_renderer(SDL_Renderer* renderer)
        {
            if (!renderer) return false;
			
            this->m_renderer = renderer;
            return true;
        }

        /**
         * @brief Loads a texture from a filesystem path (relative to executable).
         * @param path Relative path to the texture file (supports PNG, JPG, etc.).
         * @param mode Scaling filter mode (default: SDL_SCALEMODE_LINEAR).
         * @return Pointer to SDL_Texture on success, nullptr on failure.
         * @throws std::runtime_error if renderer isn't initialized or file is missing.
         */
        SDL_Texture* load_texture_relative(const std::filesystem::path& path, SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR);
    };
}