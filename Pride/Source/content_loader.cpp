#include "pride/content_loader.h"
#include "pride/texture.h"

void Pride::ContentLoader::register_asset_relative(
  const std::string_view name, const std::filesystem::path &path,
  SDL_ScaleMode mode
)
{
  if (!this->m_renderer)
  {
    SDL_Log("ERROR: TEXTURE: The renderer is not initialised.");
    return;
  }

  if (this->assets.find(name) != this->assets.end())
  {
    SDL_Log("WARNING: TEXTURE: Asset already exists, overwriting.");
  }

  auto result = this->assets.insert_or_assign(name, Pride::Texture::from_relative_path(path, this->m_renderer));
  result.first->second.set_filter(mode);
}

