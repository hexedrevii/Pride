#pragma once

#include <memory>

#include "world.h"

namespace Pride
{
    /// @brief Represents a world handler.
    class Universe
    {
    private:
        std::unique_ptr<World> m_active;
    public:
        /// @brief Set the active world.
        void set(std::unique_ptr<World> next);

        template<typename TWorld, typename... TArgs>
        void set(TArgs&&... args);

        /// @brief Process the world.
        void process();

        /// @brief Render the world.
        void render();
    };

    inline void Universe::set(std::unique_ptr<World> next)
    {
        if (this->m_active != nullptr)
        {
            this->m_active->leave();
        }

        this->m_active = std::move(next);
        this->m_active->awake();
    }

    template<typename TWorld, typename... TArgs>
    inline void Universe::set(TArgs&&... args)
    {
        static_assert(std::is_base_of<World, TWorld>::value, "TWorld must derive from World");

        if (this->m_active != nullptr)
        {
            this->m_active->leave();
        }

        this->m_active = std::make_unique<TWorld>(std::forward<TArgs>(args)...);
        this->m_active->awake();
    }

    inline void Universe::process()
    {
        if (this->m_active != nullptr)
        {
            this->m_active->process();
        }
    }

    inline void Universe::render()
    {
        if (this->m_active != nullptr)
        {
            this->m_active->render();
        }
    }
}