#include "world.h"
#include "../components/timer.h"

using namespace VB;

uint16_t Component::id() const
{
    return m_id;
}

Entity * Component::entity()
{
    return m_entity;
}

void Component::entity(Entity *entity)
{
    m_entity = entity;
}

void Component::destroy() {}
void Component::awake() {}
void Component::added() {}
void Component::destroyed() {}

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::destroy()
{
    m_world->destroy(this);
}

Vector<Component*> &Entity::components() {
    return m_components;
}

const Vector<Component*> &Entity::components() const {
    return m_components;
}

template<class T>
T* Entity::add(T&& component)
{
    return m_world->add(this, std::forward<T>(component));
}

World::World()
{
    m_cache.clear();
    m_alive.clear();
    m_components_cache.clear();
    m_components_alive.clear();
}

World::~World()
{
    clear();
}

void World::clear()
{
    m_alive.clear();
    m_cache.clear();
    m_components_cache.clear();
    m_components_alive.clear();
}

void World::update()
{

}

void World::render(Batch &batch)
{

}

Entity* World::create(Point position, Point scale, float rotation)
{
    // create entity instance
    Entity* instance;
    if (m_cache.first())
    {
        instance = m_cache.first();
        m_cache.recycle(instance);
        *instance = Entity();
    }
    else
    {
        instance = m_alive.create();
    }

    // assign
    instance->position(position);
    instance->scale(scale);
    instance->rotation(rotation);
    instance->world(this);

    // return new entity!
    return instance;
}

void World::destroy(Entity* entity)
{
    if (entity && entity->world() == this)
    {
        // destroy components
        for (int i = entity->components().size() - 1; i >= 0; i--)
            destroy(entity->components()[i]);

        // remove ourselves from the list
        m_alive.recycle(entity);
        m_cache.create();

        // done
        entity->world(nullptr);
    }
}

void World::destroy(Component* component)
{

}