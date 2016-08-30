#include <iostream>
#include <cstdlib>
#include <cmath>

#include <SDL.h>
#include <time.h>

#include "vector3.h"
#include "sphere.h"

#include "simulation.h"

int main(int argc, char* argv[])
{
    double grav =  0;
    double drag = 0.5;
    double rest = 5;
    double force = 0;
	int nSpheres = 15;

    if (argc == 5)
    {
        grav  = atof(argv[1]);
        drag  = atof(argv[2]);
        rest  = atof(argv[3]);
        force = atof(argv[4]);
		nSpheres = atoi(argv[5]);
	}
    else
    {
		std::cout << "USAGE: simulation [gravity][drag][rest velocity][bounce force][number of spheres]" << std::endl;
        std::cout << "Wrong number of arguments. They will be set to 0 1 1 1 15" << std::endl;
    }

    //seed random
    srand(time(NULL));
    Simulation s;

    //set constants
    Sphere::setGravity(-grav);
    Physics::setDrag(drag);
    Physics::setRestSpeed(rest);
    Physics::setForce(force);

    s.init();

    for (int i = 0; i < 15; i++)
    {
        // Maximum aggroRange is half the distance between opposite corners of a 100x100x100 cube
        Entity* e = new Sphere(Vector3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20),
                               Vector3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20),
                               (float)((rand() % 10) + 4) / 4, (float)((rand() % 10) + 4) / 4);
        s.addEntity(e);
    }

    s.run();

    s.shutdown();

    return 0;
}