#pragma once

#include <SDL3/SDL.h>

namespace Pride::Math
{
    class Vec2
    {
    public:
        float x, y;

        Vec2(float x, float y) : x(x), y(y) {};
        Vec2(float value) : x(value), y(value) {};

        Vec2() : x(0), y(0) {};

        /// Convert the Vector2 to SDL_Point
        SDL_Point as_point() const
        {
            return SDL_Point {static_cast<int>(this->x), static_cast<int>(this->y)};
        }


        bool operator==(Vec2 const& rhs) const
        {
            return this->x == rhs.x && this->y == rhs.y;
        }


        Vec2 operator+(Vec2 const& rhs) const
        {
            return Vec2(this->x + rhs.x, this->y + rhs.y);
        }

        Vec2 operator+(float const& rhs) const
        {
            return Vec2(this->x + rhs, this->y + rhs);
        }


        Vec2 operator-(Vec2 const& rhs) const
        {
            return Vec2(this->x - rhs.x, this->y - rhs.y);
        }

        Vec2 operator-(float const& rhs) const
        {
            return Vec2(this->x - rhs, this->y - rhs);
        }


        Vec2 operator*(float scalar) const
        {
            return Vec2(this->x * scalar, this->y * scalar);
        }


        Vec2 operator/(float scalar) const
        {
            if (scalar != 0)
            {
                return Vec2(this->x / scalar, this->y / scalar);
            }
            else
            {
                return Vec2();
            }
        }
    };
}