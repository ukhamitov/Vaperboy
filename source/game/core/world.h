#pragma once
#include <blah.h>
#include "transform.h"

using namespace Blah;

namespace VB
{
    class World;
    class Entity;

    // --------------------- //
    //                       //
    //    COMPONENT CLASS    //
    //                       //
    // --------------------- //
    class Component
    {
        friend class World;
        friend class Entity;

    private:
        // Unique Component ID
        uint16_t m_id = 0;

        // Reference to our Parent Entity
        Entity* m_entity = nullptr;

        // Previous Component in the Linked list
        Component* m_prev = nullptr;

        // Next Component in the Linked list
        Component* m_next = nullptr;

    public:
        // Whether the Component is enabled
        bool enabled = true;

        // Mask bit flags, used for various things like collision masks
        uint32_t mask = 1 << 0;

        // Returns the unique Component ID
        uint16_t id() const;

        // Returns a pointer to the world this Component belongs to
        World* world();

        // Returns a pointer to the world this Component belongs to
        const World* world() const;

        // Returns an EntityRef is the Entity this Component belongs to
        Entity* entity();

        //
        void entity(Entity* entity);

        // Destroys the Component, removes it from its Entity & World
        void destroy();

        // Called when the Component "wakes up", before the first update
        virtual void awake();

        // Called immediately after the Component is added
        virtual void added();

        // Called when the Component is finally Removed (at the end of the frame)
        virtual void destroyed();

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


    // -------------------- //
    //                      //
    //     ENTITY CLASS     //
    //                      //
    // -------------------- //
    class Entity : public Transform
    {
        friend class World;

    public:
        Entity();
        ~Entity();

        // World the Entity is a part of
        World* world() { return m_world; }
        void world(World* world) { m_world = world; }

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


    // --------------------- //
    //                       //
    //      WORLD CLASS      //
    //                       //
    // --------------------- //
    class World
    {
    public:
        World();
        ~World();
        void clear();

        // update / render
        void update();
        void render(Batch& batch);

        // entity methods
        Entity* create(Point position = Point::zero, Point scale = Point::one, float rotation = 0.0f);
        void destroy(Entity* entity);

        // component methods
        template<class T>
        T* add(Entity* entity, T&& component = T());
        void destroy(Component* component);

    private:
        // used to pool game objects
        // recycles objects and uses linked-lists for "alive" and "dead"
        template<class T>
        class ObjectPool
        {
        private:
            static constexpr int bucket_size = 64;
            Vector<StackVector<T, bucket_size>*> m_buckets;
            T* m_first = nullptr;
            T* m_last = nullptr;
            T* m_destroyed = nullptr;

        public:
            ~ObjectPool() { clear(); }
            T* first() const { return m_first; }
            T* last() const { return m_last; }

            T* create()
            {
                T* instance = nullptr;
                if (m_destroyed != nullptr)
                {
                    instance = m_destroyed;
                    m_destroyed = (T*)m_destroyed->next();
                }
                else
                {
                    if (m_buckets.size() <= 0 || m_buckets.back()->size() >= bucket_size)
                        m_buckets.push_back(new StackVector<T, bucket_size>());

                    m_buckets.back()->emplace_back();
                    instance = &m_buckets.back()->back();
                }

                if (m_first == nullptr)
                {
                    m_first = m_last = instance;
                    instance->next(nullptr);
                    instance->prev(nullptr);
                }
                else
                {
                    m_last->next(instance);
                    instance->prev(m_last);
                    instance->next(nullptr);
                    m_last = instance;
                }

                return instance;
            }

            void recycle(T* instance)
            {
                auto prev = (T*)instance->prev();
                auto next = (T*)instance->next();

                if (m_first == instance) m_first = next;
                if (m_last == instance) m_last = prev;
                if (prev) prev->next(next);
                if (next) next->prev(prev);

                instance->prev(nullptr);
                instance->next(m_destroyed);
                m_destroyed = instance;
            }

            void clear()
            {
                for (auto& it : m_buckets) delete it;
                m_buckets.clear();
                m_first = nullptr;
                m_last = nullptr;
                m_destroyed = nullptr;
            }
        };

        ObjectPool<Entity> m_cache;
        ObjectPool<Entity> m_alive;
        ObjectPool<Component> m_components_cache;
        ObjectPool<Component> m_components_alive;
    };

    template<class T>
    T* World::add(Entity* entity, T&& component)
    {
        BLAH_ASSERT(entity, "Entity cannot be null");
        BLAH_ASSERT(entity->m_world == this, "Entity must be part of this world");

        // return new entity!
        return nullptr;
    }
}