#ifndef _SPHERE_H
#define _SPHERE_H

#include "entity.h"

/*
    Sphere specialization of entity
*/
class Sphere : public Entity
{
protected:
    //sphere specific properties
    float radius;

public:
    //constructor
    Sphere(Vector3& pos, Vector3& vel, float mass, float radius);

    /*
        Overrides entity's draw.
        Draws a sphere in the entity's position
    */
    virtual void draw();
    /*
        Overrides entity's collidewith.
        Checks for colision
    */
    virtual bool collidesWith(Entity* e);

    //radius getter
    float getRadius();

};

#endif