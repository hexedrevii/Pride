#pragma once

namespace Pride
{
    /// @brief Represents the default world class.
    class World
    {
    public:
        /// @brief Ran once when the world is created.
        virtual void awake() {};

        /// @brief Ran every frame before render.
        virtual void process() {};

        /// @brief Ran every frame after process.
        virtual void render() {};

        /// @brief Ran when the world is changed by the universe.
        virtual void leave() {};
    };
}