#ifndef SCENEOBJECTS_H
#define	SCENEOBJECTS_H

#include "Model.h"
#include "Vector3.h"


class SceneObject {
public:
    SceneObject();
    void setPosition (int x, int y);
    void setDirection (float x, float y);
    virtual void draw() {};

    float x, z;
    float y;
    Vector3 direction;
    
};


class SceneObjectShip : public SceneObject {
public:
    SceneObjectShip();
    void setCannonDirection(float x, float y);
    void draw();
    
private:
    Vector3 cannonDirection;
    Model* shipModel;
    Model* cannonModel;
    
};

class SceneObjectProjectile : public SceneObject {
public:
    SceneObjectProjectile();
    void draw();
    
private:
    Model* projectileModel;
    
};

#endif	/* SCENEOBJECTS_H */

