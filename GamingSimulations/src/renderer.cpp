#include "renderer.h"

//std::vector<Entity*> Renderer::entities;

Renderer::Renderer()
{
    screenWidth  = 800;
    screenHeight = 600;

    window = NULL;
}

void Renderer::addEntity(Entity* e)
{
    if (e)
    {
        entities.push_back(e);
    }
}

void Renderer::renderScene()
{
    for (unsigned i = 0; i < entities.size(); i++)
    {
        this->entities[i]->draw();
    }
}


bool Renderer::init()
{
    //init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Call to SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    //create window
    window = SDL_CreateWindow("Gaming Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Call to SDL_CreateWindow: " << SDL_GetError() << "\n";
        return false;
    }

    //opengl version 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //setup opengl context
    glContext = SDL_GL_CreateContext(window);

    if (glContext == NULL)
    {
        std::cout << "Call to SDL_GL_CreateContext failed: " << SDL_GetError() << "\n";
        return false;
    }

    //opengl initialisation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 8.0f/6, 1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    //set camera (static)
    glLoadIdentity();
    gluLookAt(0, 0, -15,
        0, 0, 0,
        0, 1, 0);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "failed to initialise GLEW";

    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 1);

    return true;
}

void Renderer::renderPlanes()
{
    GLfloat red[] = { .5f, .0f, .0f, .3f };
    GLfloat blue[] = { 0.f, .0f, .5f, .3f };
    GLfloat white[] = { .7f, .7f, .7f, .3f };


    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    glVertex3f(-10, -10, 0);
    glVertex3f(-10, 10, 0);
    glVertex3f(-10, 10, 20);
    glVertex3f(-10, -10, 20);


    glVertex3f(10, -10, 20);
    glVertex3f(10, 10, 20);
    glVertex3f(10, 10, 0);
    glVertex3f(10, -10, 0);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);

    glVertex3f(10, -10, 0);
    glVertex3f(-10, -10, 0);
    glVertex3f(-10, -10, 20);
    glVertex3f(10, -10, 20);


    glVertex3f(10, 10, 20);
    glVertex3f(-10, 10, 20);
    glVertex3f(-10, 10, 0);
    glVertex3f(10, 10, 0);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);

    glVertex3f(10, -10, 20);
    glVertex3f(-10, -10, 20);
    glVertex3f(-10, 10, 20);
    glVertex3f(10, 10, 20);


    glVertex3f(10, -10, 0);
    glVertex3f(-10, -10, 0);
    glVertex3f(-10, 10, 0);
    glVertex3f(10, 10, 0);


    glEnd();
}

void Renderer::update()
{
    //clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //draw entities
    renderScene();
    //draw cube boundaries
    renderPlanes();
}

bool Renderer::shutdown()
{
    SDL_DestroyWindow(window);
    window = NULL;

    return true;
}