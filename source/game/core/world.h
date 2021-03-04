#pragma once
#include <blah.h>
#include "component.h"
#include "entity.h"

using namespace Blah;

namespace VB
{
    class Component;
    class Entity;

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

        static const int max_component_types = 256;

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

        uint16_t m_unique_id;
        //Vector<Component*> m_components;
        ObjectPool<Entity> m_cache;
        ObjectPool<Entity> m_alive;
        //ObjectPool<Component> m_components_cache[max_component_types];
        //ObjectPool<Component> m_components_alive[max_component_types];
    };

    template<class T>
    T* World::add(Entity* entity, T&& component)
    {
        // instantiate a new instance
        T* instance = new T();
        //instance->m_entity = entity;
        return instance;
    }
}