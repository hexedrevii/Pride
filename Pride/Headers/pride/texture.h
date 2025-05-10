#pragma once

#include "pride/vec2.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <filesystem>
#include <memory>
namespace Pride
{
  struct SDLTextureDestroyer
  {
    void operator()(SDL_Texture* legacy)
    {
      SDL_DestroyTexture(legacy);
    }
  };

  /// @brief Safe SDL_Texture wrapper.
  class Texture
  {
  public:
    int width, height;

    // ?
    Texture() {}

    Texture(const std::filesystem::path& path, SDL_Renderer* render);
    Texture(Math::Vec2 size, SDL_PixelFormat format, SDL_TextureAccess access, SDL_Renderer* render);
    Texture(int width, int height, SDL_PixelFormat format, SDL_TextureAccess access, SDL_Renderer* render);

    static Texture from_relative_path(const std::filesystem::path& path, SDL_Renderer* render);

    void set_filter(SDL_ScaleMode mode);

    operator SDL_Texture*() const {
      return this->m_texture.get();
    }
  private:
    std::unique_ptr<SDL_Texture, SDLTextureDestroyer> m_texture;
  };
}
