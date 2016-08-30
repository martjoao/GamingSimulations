#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <vector>
#include <list>
#include "sphere.h"

/*
    Physics Class
    Handles physics of movement and collision
*/

class Physics
{
protected:
    //vector of all entities that may be subject to physics
    std::vector<Entity*> entities;

    //vector of all entities that are not in REST state
    std::list<Entity*> moving;

    //Constant that simulates a drag force (sould be between 0 and 1)
    static double DRAG;

    //If entity's speed is under REST_SPEED, it is set to 0
    static double REST_SPEED;

    //force applied to sphere once it hits wall
    static double FORCE;


    //Position updates. Calls one of the numeric integration methods 
    bool updatePosition(Entity*, float sec);

    //Semi implicit Euler integration method for computing position and velocity updates
    bool eulerSemiImplicit(Entity*, float sec);

    //calculates the impulse after a collision has occured
    void impulse(Entity* a, Entity* b);

    //checks if an entity colided with the world boundaries(cube) and make it bounce back
    bool collideWithBoundaries(Entity* e);

public:
    //adds an entity to entity list and moving list
    void addEntity(Entity* e);    

    //initialisation routine
    bool init();

    //frame update routine
    void update(float sec);

    //shutdown routine
    bool shutdown();

    //static setters and getters
    static void setDrag(double d);
    static void setRestSpeed(double d);
    static void setForce(double d);
    static double getForce();

};

#endif