#include "SceneObjects.h"
#include "AssetLoader.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "Scene.h"



//------------------------------------------------------------------------------
//SceneObject
//------------------------------------------------------------------------------


SceneObject::SceneObject() {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->direction = Vector3(-1.0, 0.0, 0.0);

}

void SceneObject::setPosition(int x, int y) {
    this->x = ((float)x/800.0)*Scene::water->edge;
    this->z = ((float)y/800.0)*Scene::water->edge;

}

void SceneObject::setDirection(float x, float y) {
    this->direction = Vector3(-x, 0.0, y);
    this->direction.normalize();
    
}
//


//------------------------------------------------------------------------------
//SceneObjectShip
//------------------------------------------------------------------------------


SceneObjectShip::SceneObjectShip() {
    this->shipModel = &AssetLoader::models[0];
    this->cannonModel = &AssetLoader::models[1];   
    this->cannonDirection = Vector3(-1.0, 0.0, 0.0);
    
} 

void SceneObjectShip::setCannonDirection(float x, float y) {
    this->cannonDirection = Vector3(-x, 0.0, y);
    this->cannonDirection.normalize();
    
}
    
void SceneObjectShip::draw() {
    
    glPushMatrix();
        this->y = Scene::water->calcHeight(this->x, this->z);
        
        Vector3 p1 = Vector3(this->x, this->y, this->z) - this->direction;
        p1.y = Scene::water->calcHeight(p1.x, p1.z);
        Vector3 p2 = Vector3(this->x, this->y, this->z) + this->direction;  
        p2.y = Scene::water->calcHeight(p2.x, p2.z);
        Vector3 fixedDirection = p2-p1;
        
        fixedDirection.normalize();
        fixedDirection.set(sqrt(1.0-(fixedDirection.y*fixedDirection.y)), 0.0, fixedDirection.y);
        float angle = (Vector3::getEulerAngles(fixedDirection));
        
        
        
        glTranslatef(this->x, this->y, this->z);
        
        glPushMatrix();
            glRotatef(Vector3::getEulerAngles(this->direction), 0, 1, 0);
            glRotatef(angle, 0, 0, 1);
            this->shipModel->draw();
            
        glPopMatrix();

        glPushMatrix();
            glRotatef(Vector3::getEulerAngles(this->direction), 0, 1, 0);
            glRotatef(angle, 0, 0, 1);
            glRotatef(-Vector3::getEulerAngles(this->direction), 0, 1, 0);
            glRotatef(Vector3::getEulerAngles(this->cannonDirection), 0, 1, 0);
            
            this->cannonModel->draw();
        glPopMatrix();
        
    glPopMatrix();
    
}

//------------------------------------------------------------------------------
//SceneObjectProjectile
//------------------------------------------------------------------------------


SceneObjectProjectile::SceneObjectProjectile() {
    this->projectileModel = &AssetLoader::models[2];
    this->y = 0.5;
}

void SceneObjectProjectile::draw() {
    
    glPushMatrix();
        glTranslatef(this->x, this->y, this->z);
        this->projectileModel->draw();
        
    glPopMatrix();
    
}