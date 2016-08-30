#ifndef _GAME_ENTITY
#define _GAME_ENTITY

#include "vector3.h"
#include <GL\glew.h>

/*
    enum for shape values
*/
enum Shape
{
    SHAPE_NONE    = 0,
    SHAPE_SPHERE  = 1,
    SHAPE_PLANE   = 2
};

/*
    enum for state values
*/
enum State
{
    REST = 1,
    MOVE = 0
};

/*
    Base entity class
*/
class Entity
{
protected:
    //entity properties
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    float mass;
    Shape shape;
    //state is either at rest or moving
    State state;

    static double gravity;

public:
    Entity();
    Entity(Vector3& pos, Vector3& vel, float mass);

    /*
        draws graphical representation of entity on screen
    */
    virtual void draw() = 0;
    
    /*
        checks for collision with entity e
    */
    virtual bool collidesWith(Entity* e) = 0;

    //getters
    Vector3& getPosition();
    Vector3& getVelocity();
    Vector3& getAcceleration();
    float getMass();
    Shape getShape();
    State getState();

    //setters
    void setPosition(const Vector3& vec);
    void setVelocity(const Vector3& vec);
    void setAcceleration(const Vector3& vec);
    void setMass(float mass);
    void setState(State s);
    static void setGravity(double g);


};

#endif