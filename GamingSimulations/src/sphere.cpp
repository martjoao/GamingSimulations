#include "sphere.h"

Sphere::Sphere(Vector3& pos, Vector3& vel, float m, float radius) : Entity(pos, vel, m)
{
    this->radius = radius;
    shape = SHAPE_SPHERE;
    acceleration = Vector3(0, gravity, 0);
}

void Sphere::draw()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //translates sphere to its position
    glTranslated(position.x, position.y, position.z);

    //colour
    GLfloat cyan[] = { 0.f, .8f, .8f, 1.f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);

    //draw sphere (using GLU)
    GLUquadricObj *qobj = NULL;
    qobj = gluNewQuadric();

    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricOrientation(qobj, GLU_OUTSIDE);
    gluSphere(qobj, radius, 30, 30);
    gluDeleteQuadric(qobj);


    glPopMatrix();
}

bool Sphere::collidesWith(Entity* e)
{

    if (this == e)
    {
        //sphere does not collide with itself
        return false;
    }
    else if (e->getShape() == SHAPE_SPHERE)
    {
        //checks for sphere-sphere collision
        Vector3 aPos = position;
        Vector3 bPos = e->getPosition();

        //vector from center of a sphere to another
        Vector3 diff = aPos - bPos;

        //distance
        double dist = sqrt(diff.dot(diff));
        double sumRadius = radius + ((Sphere*)e)->getRadius();

        //if distance is smaller than sum of both radius
        if (dist < sumRadius)
        {
            //fix overlapping
            Vector3 projection = diff.normalise() * (sumRadius - dist);
            position += projection;
            return true;
        }

    }
    return false;
}

float Sphere::getRadius()
{
    return radius;
}

