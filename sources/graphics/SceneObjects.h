#ifndef SCENEOBJECTS_H
#define	SCENEOBJECTS_H

#include "Model.h"
#include "Vector3.h"
#include <string>

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
    static float viewAngle;
    static float viewRange;
    static void setViewAngle(float angle);
    static void setViewRange(float range);
    
    SceneObjectShip();
    void setCannonDirection(float x, float y);
    void setViewDirection(float x, float y);
    void draw();
    void setDescription(string desc);
    
private:
    Vector3 cannonDirection;
    Vector3 viewDirection;
    Model* shipModel;
    Model* cannonModel;
    string  description;
            
};

class SceneObjectProjectile : public SceneObject {
public:
    SceneObjectProjectile();
    void draw();
    
private:
    Model* projectileModel;
    
};

#endif	/* SCENEOBJECTS_H */

