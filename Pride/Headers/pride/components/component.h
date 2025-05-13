#pragma once

#include <SDL3/SDL_events.h>
namespace Pride
{
  class Entity; // Forward decl because C++ is ass.

  class Component
  {
  public:
    /// @brief Entity parent of the component
    Entity *parent = nullptr;

    int id = -1;

    /// @brief Should be called once when an event happens.
    virtual void event(const SDL_Event& event) {};

    /// @brief Should be called every frame, before render.
    virtual void render() {};

    /// @brief Should be called every frame, after process.
    virtual void process(float delta) {};

    /// @brief Should be called once, when the component is destroyed.
    virtual void leave() {};
  };
} // namespace Pride
