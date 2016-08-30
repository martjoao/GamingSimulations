#include "simulation.h"

void Simulation::addEntity(Entity* e)
{
    if (e)
    {
        entities.push_back(e);
        renderer->addEntity(e);
        physics->addEntity(e);
    }
}

void Simulation::deleteEntities()
{
    for (unsigned i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
}

bool Simulation::init()
{
    renderer = new Renderer();
    timer    = new GameTimer();
    physics  = new Physics();

    renderer->init();
    timer->init();
    physics->init();

    return true;
}

void Simulation::run()
{
    //Physics timestep is fixed and rendering timestep is variable
    
    float timestep = 1.f/ 30;
    float timestepMilis = timestep * 1000;

    float previousTime = timer->currentTime();
    float t = 0;
    while (true)
    {
        float currentTime = timer->currentTime();
        float elapsed = currentTime - previousTime;
        t = t + elapsed;        

        //if quit
        SDL_Event inputEvent;
        if (SDL_PollEvent(&inputEvent))
        {
            if (inputEvent.type == SDL_QUIT)
            {
                std::cout << "QUIT SIGNAL RECEIVED";
                break;
            }
        }
        
        while (t >= timestepMilis)
        {
            physics->update(timestep);
            t -= timestepMilis;
        }
        
        //clear screen and render (graphical)
        renderer->update();

        //swap buffers
        SDL_GL_SwapWindow(renderer->getWindow());

        //update previous time to time at beginning of frame
        previousTime = currentTime;
    }

}

bool Simulation::shutdown()
{
    //cleanup and prepare for shutdown
    deleteEntities();

    physics->shutdown();
    timer->shutdown();
    renderer->shutdown();

    physics = NULL;
    timer = NULL;
    renderer = NULL;

    return true;
}