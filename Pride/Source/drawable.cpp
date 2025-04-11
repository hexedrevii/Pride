#include "pride/drawable.h"

void Pride::Drawable::draw_texture(SDL_Texture* texture, Pride::Math::Vec2 position, Pride::Colour tint)
{
	this->draw_texture(texture, position, 1.0f, tint);
}

void Pride::Drawable::draw_texture(SDL_Texture* texture, Pride::Math::Vec2 position, float scale, Pride::Colour tint)
{
	SDL_SetTextureColorMod(texture, tint.r, tint.g, tint.b);

	SDL_FRect rect = SDL_FRect { position.x, position.y, texture->w * scale, texture->h * scale };
	SDL_RenderTexture(this->m_renderer, texture, nullptr, &rect);
}