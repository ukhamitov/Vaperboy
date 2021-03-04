#include "world.h"
#include "../components/timer.h"

using namespace VB;

World::World()
{
    m_unique_id = 0;
    //for (int i = 0; i < 256; i++)
    //    m_components.push_back(nullptr);
    m_cache.clear();
    m_alive.clear();
}

World::~World()
{
    clear();
}

void World::clear()
{
    m_alive.clear();
    m_cache.clear();
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