#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <SDL.h>

#include "entity.h"

/*
    Renderer Class
    Deals with setting up window and drawing elements on screen 
    Uses SDL for window management and OpenGL (2.1) for graphics
*/
class Renderer
{
protected:
    //vector with every entity that is renderable
    std::vector<Entity*> entities;

    //window properties
    int screenWidth;
    int screenHeight;

    //window
    SDL_Window* window;

    //opengl context
    SDL_GLContext glContext;

public:
    Renderer();

    //window getter
    SDL_Window* getWindow() { return window; }
    
    //adds entity to list of renderable entities
    void addEntity(Entity* e);

    //render every entity on list
    void renderScene();

    //render planes that bounds scene (cube)
    void renderPlanes();

    //window and graphics initialisation routine
    bool init();

    //frame rendering routine
    void update();

    //shutdown routine
    bool shutdown();
};

#endif