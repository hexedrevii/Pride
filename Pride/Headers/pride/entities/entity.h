#pragma once

#include "../components/component.h"
#include "../vec2.h"

#include <memory>
#include <vector>

namespace Pride
{
  class Entity
  {
  public:
    Pride::Math::Vec2 position = Pride::Math::Vec2();
    Pride::Math::Vec2 velocity = Pride::Math::Vec2();

    /// @brief Add a new component to the entity.
    /// @tparam TComponent The component type.
    /// @param ...args The constructor arguments for the component.
    template <typename TComponent, typename... TArgs>
    void enroll_component(TArgs &&...args);

    /// @brief Add a new component to the entity.
    /// @param component The component to add.
    void enroll_component(std::shared_ptr<Component> component);

    /// @brief Should be called once when the entity is first created.
    virtual void awake() {};

    /// @brief Should be called every frame, before render.
    virtual void process(float delta) {};

    /// @brief Should be called every frame, after process.
    virtual void render() {};

    /// @brief Should be called once, when the entity is destroyed.
    virtual void leave() {};

    /// @brief This processes the components then the entity.
    void update(float delta)
    {
      for (std::shared_ptr<Component> &component : this->m_components)
      {
        component->process(delta);
      }

      this->process(delta);
    }

    /// @brief THis renders the components then the entity.
    void draw()
    {
      for (std::shared_ptr<Component> &component : this->m_components)
      {
        component->render();
      }

      this->render();
    }

    /// @brief This calls leave() on all components then the entity.
    void destroy()
    {
      for (std::shared_ptr<Component> &component : this->m_components)
      {
        component->leave();
      }

      this->leave();
    }

  private:
    std::vector<std::shared_ptr<Component>> m_components;
  };

  template <typename TComponent, typename... TArgs>
  inline void Entity::enroll_component(TArgs &&...args)
  {
    static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must derive from Component");

    std::shared_ptr<TComponent> component = std::make_shared<TComponent>(std::forward<TArgs>(args)...);
    component->id = this->m_components.size();
    component->parent = this;

    this->m_components.emplace_back(component);
  }

  inline void Entity::enroll_component(std::shared_ptr<Component> component)
  {
    if (component->id == -1)
      component->id = this->m_components.size();
    if (component->parent == nullptr)
      component->parent = this;

    this->m_components.push_back(component);
  }
} // namespace Pride
