#pragma once
#include <blah.h>
#include <inttypes.h>
#include "transform.h"
#include "component.h"

namespace VB
{
    class Component;
    class World;

    class Entity : public Transform
    {
    public:
        Entity();
        ~Entity() override;

        // World the Entity is a part of
        inline World* world() { return m_world; }
        inline void world(World* world) { m_world = world; }

        // Previous Entity in the Linked List
        inline Entity* prev() { return m_prev; }
        inline void prev(Entity* entity) { m_prev = entity; }

        // Next Entity in the Linked List
        inline Entity* next() { return m_next; }
        inline void next(Entity* entity) { m_next = entity; }

        template<class T>
        T* add(T&& component = T());

        Vector<Component*>& components();
        const Vector<Component*>& components() const;

        void destroy();

    private:
        // World the Entity is a part of
        World* m_world = nullptr;

        // Previous Entity in the Linked List
        Entity* m_prev = nullptr;

        // Next Entity in the Linked List
        Entity* m_next = nullptr;

        // List of all our Components
        Vector<Component*> m_components;
    };

    template<class T>
    T* Entity::add(T&& component)
    {
//        return m_world->add(this, std::forward<T>(component));
        return nullptr;
    }
}