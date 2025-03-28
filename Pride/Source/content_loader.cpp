#include "pride/content_loader.h"
#include <string>

SDL_Texture* Pride::ContentLoader::load_texture_relative(const std::filesystem::path& path, SDL_ScaleMode mode)
{
	const char* base = SDL_GetBasePath();
	if (!base)
	{
		SDL_Log("ERROR: TEXTURE: Cannot load base executable path.");
		return nullptr;
	}

	std::filesystem::path full = base / path;
	std::string legacy = full.string();

	SDL_Texture* texture = IMG_LoadTexture(this->m_renderer, legacy.c_str());
	if (!texture)
	{
		SDL_Log("ERROR: TEXTURE: Cannot load texture: %s.", SDL_GetError());
		return nullptr;
	}

	SDL_SetTextureScaleMode(texture, mode);

	return texture;
}