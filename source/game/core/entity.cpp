#include "entity.h"

using namespace VB;

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
