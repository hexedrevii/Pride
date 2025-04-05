#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <filesystem>
#include <string>

namespace Pride
{
	class ContentLoader
	{
	private:
		SDL_Renderer* m_renderer = nullptr;

	public:
		// Load the render device for content loading.
		bool load_renderer(SDL_Renderer* renderer)
		{
			if (!renderer) return false;
			this->m_renderer = renderer;

			return true;
		}

		// Loads a texture relative to the EXE position.
		SDL_Texture* load_texture_relative(const std::filesystem::path& path, SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR);
	};
}