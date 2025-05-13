#include "pride/texture.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <stdexcept>
#include <format>

Pride::Texture::Texture(const std::filesystem::path& path, SDL_Renderer* render)
{
  if (!render) throw std::runtime_error("The renderer is not initialised.");

  std::string legacy = path.string();

  SDL_Texture *tex = IMG_LoadTexture(render, legacy.c_str());
  if (!tex) throw std::runtime_error(std::format("Texture could not be loaded: {}", SDL_GetError()));

  this->width = tex->w;
  this->height = tex->h;

  this->m_texture = std::unique_ptr<SDL_Texture, Pride::SDLTextureDestroyer>(tex);
}

Pride::Texture::Texture(Math::Vec2 size, SDL_PixelFormat format, SDL_TextureAccess access, SDL_Renderer* render)
{
  SDL_Texture* tex = SDL_CreateTexture(render, format, access, size.x, size.y);
  if (!tex) throw std::runtime_error(std::format("Texture could not be loaded: {}", SDL_GetError()));

  this->width = size.x;
  this->height = size.y;

  this->m_texture = std::unique_ptr<SDL_Texture, Pride::SDLTextureDestroyer>(tex);
}

Pride::Texture::Texture(int width, int height, SDL_PixelFormat format, SDL_TextureAccess access, SDL_Renderer* render)
{
  SDL_Texture* tex = SDL_CreateTexture(render, format, access, width, height);
  if (!tex) throw std::runtime_error(std::format("Texture could not be loaded: {}", SDL_GetError()));
  this->width = width;
  this->height = height;

  this->m_texture = std::unique_ptr<SDL_Texture, Pride::SDLTextureDestroyer>(tex);
}

Pride::Texture Pride::Texture::from_relative_path(const std::filesystem::path &path, SDL_Renderer* render)
{
  const char *base = SDL_GetBasePath();
  if (!base) throw std::runtime_error("ERROR: TEXTURE: Cannot load base executable path.");

  std::filesystem::path full = base / path;
  return Texture(full, render);
}

void Pride::Texture::set_filter(SDL_ScaleMode mode)
{
  SDL_SetTextureScaleMode(this->m_texture.get(), mode);
}
