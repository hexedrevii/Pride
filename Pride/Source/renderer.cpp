#include "pride/renderer.h"


bool Pride::Renderer::create(int width, int height)
{
	if (!this->m_render)
	{
		SDL_Log("ERROR: RENDERER: Renderer doesn't exist.");
		return false;
	}

	if (!this->m_window)
	{
		SDL_Log("ERROR: SDL: Window doesn't exist.");
		return false;
	}

	this->m_renderer = SDL_CreateTexture(this->m_render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	if (!this->m_renderer)
	{
		SDL_Log("ERROR: RENDERER: Cannot create render target.");
		return false;
	}

	this->m_height = height;
	this->m_width = width;

	SDL_Log("INFO: RENDERER: Created render target.");

	return true;
}

void Pride::Renderer::attach()
{
	SDL_SetRenderTarget(this->m_render, this->m_renderer);
}

void Pride::Renderer::detach()
{
	SDL_SetRenderTarget(this->m_render, nullptr);
}

void Pride::Renderer::detach_and_draw()
{
	SDL_SetRenderTarget(this->m_render, nullptr);

	int width, height;
	SDL_GetWindowSize(this->m_window, &width, &height);

	float scale = std::min(
		static_cast<float>(width) / this->m_width,
		static_cast<float>(height) / this->m_height
	);

	SDL_FRect dst = SDL_FRect(
		(width - (this->m_width * scale)) * 0.5f,
		(height - (this->m_height * scale)) * 0.5f,
		this->m_width * scale, this->m_height * scale
	);

	SDL_FRect src = SDL_FRect(0, 0, this->m_renderer->w, this->m_renderer->h);

	SDL_RenderTexture(this->m_render, this->m_renderer, nullptr, &dst);
}