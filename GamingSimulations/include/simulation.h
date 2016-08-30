#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "gametimer.h"
#include "physics.h"
#include "renderer.h"

/*
    Simulation Class
    Puts everything together and runs the simulation
*/
class Simulation
{
protected:
    //lists of all entities. Entities management is through this list
    std::vector<Entity*> entities;

    //Time, physics and renderer Managers
    GameTimer* timer;
    Physics*   physics;
    Renderer*  renderer;

public:
    //adds entity to lists of entity on managers and simulation classes
    void addEntity(Entity* e);

    //deletes every entity on the game
    void deleteEntities();

    //initialises every manager
    bool init();
    //run simulation
    void run();
    //cleanup and shutdown
    bool shutdown();
};

#endif