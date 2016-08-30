#include "entity.h"
double Entity::gravity = 0;

Entity::Entity() : position(Vector3()), velocity(Vector3()), mass(1), shape(SHAPE_NONE), state(MOVE)
{
}

Entity::Entity(Vector3& pos, Vector3& vel, float m) : position(pos), velocity(vel), mass(m), shape(SHAPE_NONE), state(MOVE)
{
}

Shape Entity::getShape()
{
    return shape;
}
Vector3& Entity::getPosition()
{
    return position;
}

Vector3& Entity::getVelocity()
{
    return velocity;
}

Vector3& Entity::getAcceleration()
{
    return acceleration;
}

float Entity::getMass()
{
    return mass;
}

State Entity::getState()
{
    return state;
}

void Entity::setPosition(const Vector3& vec)
{
    position = vec;
}

void Entity::setVelocity(const Vector3& vec)
{
    velocity = vec;
}

void Entity::setAcceleration(const Vector3& vec)
{
    acceleration = vec;
}

void Entity::setMass(float mass)
{
    this->mass = mass;
}

void Entity::setState(State s)
{
    this->state = s;
}

void Entity::setGravity(double g)
{
    gravity = g;
}