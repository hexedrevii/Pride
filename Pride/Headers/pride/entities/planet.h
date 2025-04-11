#pragma once

#include <vector>
#include <memory>

#include "entity.h"

namespace Pride
{
    class Planet
    {
    public:
        /// @brief Enroll a new entity into the planet.
        /// @param ...args The constructor args for the entity.
        /// @return The new entity 
        template<typename TEntity, typename... TArgs>
        std::weak_ptr<TEntity> enroll(TArgs&&... args);

        /// @brief Enroll an entity to the planet. 
        /// @param entity The entity to enroll
        void enroll(std::shared_ptr<Entity> entity);

        /// @brief Should be called once a frame, before render.
        void process();
        
        /// @brief Should be called once a frame, after process.
        void render();

        /// @brief Should be called once, right before the planet is destroyed.
        void leave();
    private:
        std::vector<std::shared_ptr<Entity>> m_entities;
    };

    template<typename TEntity, typename... TArgs>
    inline std::weak_ptr<TEntity> Planet::enroll(TArgs&&... args)
    {
        // Compile-time check... C++ is not a sane language bro
        static_assert(std::is_base_of<Entity, TEntity>::value, "TEntity must derive from Entity");

        std::shared_ptr<TEntity> entity = std::make_shared<TEntity>(std::forward<TArgs>(args)...);
        entity->awake();
        
        this->m_entities.emplace_back(entity);

        return entity;
    }

    inline void Planet::enroll(std::shared_ptr<Entity> entity)
    {
        this->m_entities.push_back(entity);
    }

    inline void Planet::process()
    {
        for (std::shared_ptr<Entity>& entity : this->m_entities)
        {
            entity->update();
        }
    }

    inline void Planet::render()
    {
        for (std::shared_ptr<Entity>& entity : this->m_entities)
        {
            entity->draw();
        }
    }

    inline void Planet::leave()
    {
        for (std::shared_ptr<Entity>& entity : this->m_entities)
        {
            entity->destroy();
        }
    }
}
