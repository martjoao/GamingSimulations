#include "physics.h"

double Physics::DRAG = 1;
double Physics::REST_SPEED = 0;
double Physics::FORCE = 0;


//Euler semi implicit numeric integration method
bool Physics::eulerSemiImplicit(Entity* e, float sec)
{
    //maximum velocity
    float limit = 75;

    Vector3 s = e->getPosition();
    Vector3 v = e->getVelocity();
    Vector3 a = e->getAcceleration();

    //INTEGRATION:
    v += a*sec;
    s += v*sec;

         if (v.x >  limit)  v.x =  limit;
    else if (v.x < -limit)  v.x = -limit;
         if (v.y >  limit)  v.y =  limit;
    else if (v.y < -limit)  v.y = -limit;
         if (v.z >  limit)  v.z =  limit;
    else if (v.z < -limit)  v.z = -limit;

    e->setPosition(s);
    e->setVelocity(v*DRAG);

    //if speed is below a user defined constant, set vlocity to (0,0,0)
    if (v.norm() <= REST_SPEED && a.norm() == 0)
    {
        return false;
    }
    return true;
}

bool Physics::updatePosition(Entity* e, float sec)
{
    return eulerSemiImplicit(e, sec);
}

void Physics::addEntity(Entity* e)
{
    if (e)
    {
        entities.push_back(e);
        moving.push_back(e);
    }
}

void Physics::impulse(Entity* a, Entity* b)
{
    
    Vector3 Va = a->getVelocity();
    Vector3 Vb = b->getVelocity();
    float Ma = a->getMass();
    float Mb = b->getMass();

    Vector3 N = (a->getPosition() - b->getPosition()).normalise();
    Vector3 Vab = Va - Vb;
    double elasticity = 0.9;

    //Impulse Equation
    double J = (-(1 + elasticity) * Vab.dot(N)) / N.dot(N * ((1 / Ma) + (1 / Mb)));

    Va += N * (J / Ma);
    Vb -= N * (J / Mb);

    a->setVelocity(Va);
    b->setVelocity(Vb);
    
}

bool Physics::init()
{
    return true;
}


bool Physics::collideWithBoundaries(Entity* e)
{
    double increment = Physics::getForce() / e->getMass();


    Vector3 pos = e->getPosition();
    Vector3 vel = e->getVelocity();
    float r = ((Sphere*)e)->getRadius();

    if (pos.x - r < -10)
    {
        pos.x = -10 + r;
        vel.x = -vel.x + increment;
    }
    else if (pos.x + r > 10)
    {
        pos.x = 10 - r;
        vel.x = -vel.x - increment;
    }
    if (pos.y - r < -10)
    {
        pos.y = -10 + r;
        vel.y = -vel.y + increment;
    }
    else if (pos.y + r > 10)
    {
        pos.y = 10 - r;
        vel.y = -vel.y - increment;
    }
    if (pos.z - r < 0)
    {
        pos.z = r;
        vel.z = -vel.z + increment;
    }
    else if (pos.z + r > 20)
    {
        pos.z = 20 - r;
        vel.z = -vel.z - increment;
    }

    e->setPosition(pos);
    e->setVelocity(vel);
    return true;

}

void Physics::update(float sec)
{
    //move every entity
    for (std::list<Entity*>::iterator i = moving.begin(); i != moving.end(); )
    {
        //if its speed is below REST_SPEED
        if (!updatePosition((*i), sec))
        {
            //make it rest
            (*i)->setState(REST);
            (*i)->setVelocity(Vector3());
            i = moving.erase(i);
        }
        else
        {
            i++;
        }
    }

    //checks and resolves collision
    for (std::list<Entity*>::iterator i = moving.begin(); i != moving.end(); i++)
    {
        
        for (unsigned j = 0; j < entities.size(); j++)
        {
            //check for sphere-sphere colision
            if ((*i)->collidesWith(entities[j]))
            {
                //if spheres collided, apply impulse
                impulse((*i), entities[j]);
                if (entities[j]->getState() == REST)
                {
                    //if one of the colliding spheres is at rest, make it move
                    entities[j]->setState(MOVE);
                    moving.push_back(entities[j]);
                }
                //std::cout << "Entity " << i << " collided with Entity " << j << "\n";
            }
        }
        collideWithBoundaries(*i);
    }
}

bool Physics::shutdown()
{
    return true;
}

void Physics::setDrag(double d)
{
    DRAG = d;
}

void Physics::setRestSpeed(double d)
{
    REST_SPEED = d;
}

void Physics::setForce(double d)
{
    FORCE = d;
}

double Physics::getForce()
{
    return FORCE;
}