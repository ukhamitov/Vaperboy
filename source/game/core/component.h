#pragma once
#include <blah.h>
#include "world.h"

using namespace Blah;

namespace VB
{
    class World;

    // Components store game state and run game behaviors
    class Component
    {
        friend class World;

    private:
        // Unique Component ID
        uint16_t m_id;

        // Previous Component in the Linked list
        Component* m_prev = nullptr;

        // Next Component in the Linked list
        Component* m_next = nullptr;

    public:
        // Whether the Component is enabled
        bool enabled = true;

        // Returns the unique Component ID
        uint16_t id() const;

        // Returns a pointer to the world this Component belongs to
        World* world();

        // Returns a pointer to the world this Component belongs to
        const World* world() const;

        // Returns the Previous Component
        Component* prev() const { return m_prev; };

        // Returns the Next Component
        Component* next() const { return m_next; };
    };

    // Makes a component Updatable
    struct Updatable
    {
        float stun = 0;
        virtual void update() = 0;
    };

    // Makes a component Updatable
    struct Renderable
    {
        int depth = 0;
        virtual void render(Batch& batch) = 0;
    };
}