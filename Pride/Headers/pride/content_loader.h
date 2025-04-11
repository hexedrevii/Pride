#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <filesystem>
#include <unordered_map>

namespace Pride
{
  /**
   * @brief Handles loading and management of game assets (textures, etc.).
   * @details Requires an initialized SDL_Renderer before use.
   */
  class ContentLoader
  {
  public:
    /// @brief Asset manager for those who do not want to handle them
    /// themselves.
    std::unordered_map<std::string_view, SDL_Texture *> assets;

    /**
     * @brief Register a new asset to the asset map.
     * @param name The asset identifier.
     * @param path The relative asset path to the executable
     */
    void register_asset_relative(const std::string_view name,
                                 const std::filesystem::path &path,
                                 SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR);

    /**
     * @brief Loads a texture from a filesystem path (relative to executable).
     * @param path Relative path to the texture file (supports PNG, JPG, etc.).
     * @param mode Scaling filter mode (default: SDL_SCALEMODE_LINEAR).
     * @return Pointer to SDL_Texture on success, nullptr on failure.
     * @throws std::runtime_error if renderer isn't initialized or file is
     * missing.
     */
    SDL_Texture *
    load_texture_relative(const std::filesystem::path &path,
                          SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR);

    /**
     * @brief Initializes the content loader with a renderer.
     * @param renderer Valid SDL_Renderer pointer (must not be null).
     * @return true if renderer was set successfully, false if input was null.
     * @warning Calling asset methods before this succeeds will cause crashes.
     */
    bool load_renderer(SDL_Renderer *renderer)
    {
      if (!renderer)
        return false;

      this->m_renderer = renderer;
      return true;
    }

  private:
    SDL_Renderer *m_renderer = nullptr;
  };
} // namespace Pride
