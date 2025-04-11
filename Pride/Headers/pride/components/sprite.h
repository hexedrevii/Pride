#pragma once

#include "component.h"
#include "../drawable.h"

#include <SDL3/SDL.h>

namespace Pride
{
    class Sprite : public Component
    {
    private:
        Drawable& m_draw;
        SDL_Texture* m_texture;
    public:
        Sprite(Drawable& draw, SDL_Texture* texture) 
            : m_draw(draw), m_texture(texture) {}

        void render() override
        {
            this->m_draw.draw_texture(
                this->m_texture,
                this->parent->position,
                Colours::White
            );
        }
    };
}