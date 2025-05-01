#pragma once

#include <memory>

#include "world.h"
#include <SDL3/SDL.h>

namespace Pride
{
  /// @brief Represents a world handler.
  class Universe
  {
  public:
    /// @brief Set the active world.
    void set(std::unique_ptr<World> next);

    template <typename TWorld, typename... TArgs> void set(TArgs &&...args);

    /// @brief Handle world events.
    void event(const SDL_Event &event);

    /// @brief Process the world.
    void process(float delta);

    /// @brief Render the world.
    void render();

  private:
    std::unique_ptr<World> m_active;
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

  template <typename TWorld, typename... TArgs>
  inline void Universe::set(TArgs &&...args)
  {
    static_assert(std::is_base_of<World, TWorld>::value,
                  "TWorld must derive from World");

    if (this->m_active != nullptr)
    {
      this->m_active->leave();
    }

    this->m_active = std::make_unique<TWorld>(std::forward<TArgs>(args)...);
    this->m_active->awake();
  }

  inline void Universe::event(const SDL_Event& event)
  {
    if (this->m_active != nullptr)
    {
      this->m_active->event(event);
    }
  }

  inline void Universe::process(float delta)
  {
    if (this->m_active != nullptr)
    {
      this->m_active->process(delta);
    }
  }

  inline void Universe::render()
  {
    if (this->m_active != nullptr)
    {
      this->m_active->render();
    }
  }
} // namespace Pride
