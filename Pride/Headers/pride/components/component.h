#pragma once

#include "../entities/entity.h"

namespace Pride
{
    class Entity; // Forward decl because C++ is ass.
    
    class Component
    {
    public:
        /// @brief Entity parent of the component
        Entity* parent = nullptr;

        int id = -1;

        /// @brief Should be called every frame, before render.
        virtual void render() {};

        /// @brief Should be called every frame, after process.
        virtual void process() {};

        /// @brief Should be called once, when the component is destroyed.
        virtual void leave() {};
    };
}