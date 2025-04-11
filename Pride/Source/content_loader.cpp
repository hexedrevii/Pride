#include "pride/content_loader.h"

void Pride::ContentLoader::register_asset_relative(
    const std::string_view name, const std::filesystem::path &path,
    SDL_ScaleMode mode)
{
  if (!this->m_renderer)
  {
    SDL_Log("ERROR: TEXTURE: The renderer is not initialised.");
    return;
  }

  SDL_Texture *tex = this->load_texture_relative(path, mode);
  if (!tex)
    return;

  if (this->assets.find(name) != this->assets.end())
  {
    SDL_Log("WARNING: TEXTURE: Asset already exists, overwriting.");
    SDL_DestroyTexture(this->assets[name]);
  }

  this->assets[name] = tex;
}

SDL_Texture *
Pride::ContentLoader::load_texture_relative(const std::filesystem::path &path,
                                            SDL_ScaleMode mode)
{
  if (!this->m_renderer)
  {
    SDL_Log("ERROR: TEXTURE: The renderer is not initialised.");
    return nullptr;
  }

  const char *base = SDL_GetBasePath();
  if (!base)
  {
    SDL_Log("ERROR: TEXTURE: Cannot load base executable path.");
    return nullptr;
  }

  std::filesystem::path full = base / path;
  std::string legacy = full.string();

  SDL_Texture *texture = IMG_LoadTexture(this->m_renderer, legacy.c_str());
  if (!texture)
  {
    SDL_Log("ERROR: TEXTURE: Cannot load texture: %s.", SDL_GetError());
    return nullptr;
  }

  SDL_SetTextureScaleMode(texture, mode);

  return texture;
}
