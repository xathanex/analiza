#include "SceneObjects.h"
#include "AssetLoader.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "Printer.h"
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
    this->direction = Vector3(x, 0.0, y);
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
    
    this->description = "S";
    
} 

void SceneObjectShip::setCannonDirection(float x, float y) {
    this->cannonDirection = Vector3(x, 0.0, y);
    this->cannonDirection.normalize();
    
}

void SceneObjectShip::setViewDirection(float x, float y) {
    this->viewDirection = Vector3(x, 0.0, y);
    this->viewDirection.normalize();
    
}

float SceneObjectShip::viewAngle = 60.0;
void SceneObjectShip::setViewAngle(float angle) {
    SceneObjectShip::viewAngle = angle;
}

float SceneObjectShip::viewRange = 12.0;
void SceneObjectShip::setViewRange(float range) {
    SceneObjectShip::viewRange = ((float)range/800.0)*Scene::water->edge;
    
}

void SceneObjectShip::draw() {
    
    glPushMatrix();
        
        this->y = Scene::water->calcHeight(this->x, this->z);
        
        Vector3 p1 = Vector3(this->x, this->y, this->z) + this->direction;
        p1.y = Scene::water->calcHeight(p1.x, p1.z);
        Vector3 p2 = Vector3(this->x, this->y, this->z) - this->direction;  
        p2.y = Scene::water->calcHeight(p2.x, p2.z);
        Vector3 axisOne = p2-p1;
        
        axisOne.normalize();
        axisOne.set(sqrt(1.0-(axisOne.y*axisOne.y)), 0.0, axisOne.y);
        float angle1 = (Vector3::getEulerAngles(axisOne));
        
        Vector3 crossDirection = Vector3::crossProduct(Vector3(0.0, 1.0, 0.0), this->direction);
        crossDirection.normalize();
        Vector3 p3 = Vector3(this->x, this->y, this->z) - crossDirection/1.4;
        p3.y = Scene::water->calcHeight(p3.x, p3.z);
        Vector3 p4 = Vector3(this->x, this->y, this->z) + crossDirection/1.4;  
        p4.y = Scene::water->calcHeight(p4.x, p4.z);
        Vector3 axisTwo = p4-p3;
        
        axisTwo.normalize();
        axisTwo.set(sqrt(1.0-(axisTwo.y*axisTwo.y)), 0.0, axisTwo.y);
        float angle2 = -(Vector3::getEulerAngles(axisTwo))/2;
        
        //Rysowanie statku
        
        glTranslatef(this->x, this->y, this->z);
        
        glPushMatrix();
            glRotatef(Vector3::getEulerAngles(Vector3(-this->direction.x, 0.0, this->direction.z)), 0, 1, 0);
            glRotatef(angle2, 1, 0, 0);
            glRotatef(angle1, 0, 0, 1);
            
            this->shipModel->draw();
            
        glPopMatrix();
        
        //Rysowanie działa
        
        glPushMatrix();
            glRotatef(Vector3::getEulerAngles(Vector3(-this->direction.x, 0.0, this->direction.z)), 0, 1, 0);
            glRotatef(angle2, 1, 0, 0);
            glRotatef(angle1, 0, 0, 1);
            glRotatef(-(Vector3::getEulerAngles(Vector3(-this->direction.x, 0.0, this->direction.z))), 0, 1, 0);
            glRotatef(Vector3::getEulerAngles(Vector3(-this->cannonDirection.x, 0.0, this->cannonDirection.z)), 0, 1, 0);
            
            this->cannonModel->draw();
        glPopMatrix();
        
        Vector3 crossViewDirection = Vector3::crossProduct(Vector3(0.0, 1.0, 0.0), this->viewDirection);
        
        //Zaznaczanie pola widzenia
        
        glPushMatrix();
            glLineWidth(1.0); 
            
            glBegin(GL_LINES);
                float factor = (SceneObjectShip::viewAngle/2.0)/90.0;
                
                float vlx1 = (this->viewDirection.x*(1.0-factor) + crossViewDirection.x*factor)*SceneObjectShip::viewRange;
                float vlz1 = (this->viewDirection.z*(1.0-factor) + crossViewDirection.z*factor)*SceneObjectShip::viewRange;
                glColor4f(0.0, 0.0, 0.0, 0.5);
                glVertex3f(0.0, 1.0, 0.0);
                glColor4f(0.0, 0.0, 0.0, 0.0);
                glVertex3f(vlx1, 1.0, vlz1);
                
                float vlx2 = (this->viewDirection.x*(1.0-factor) - crossViewDirection.x*factor)*SceneObjectShip::viewRange;
                float vlz2 = (this->viewDirection.z*(1.0-factor) - crossViewDirection.z*factor)*SceneObjectShip::viewRange;
                glColor4f(0.0, 0.0, 0.0, 0.5);
                glVertex3f(0.0, 1.0, 0.0);
                glColor4f(0.0, 0.0, 0.0, 0.0);
                glVertex3f(vlx2, 1.0, vlz2);
                
    
            glEnd();

            glDisable(GL_DEPTH_TEST);
            glBegin(GL_TRIANGLES);
                
                glColor4f(1.0, 1.0, 1.0, 0.0);
                glVertex3f(vlx1, 1.0, vlz1);
                
                glColor4f(1.0, 1.0, 1.0, 0.3);
                glVertex3f(0.0, 1.0, 0.0);
                
                glColor4f(1.0, 1.0, 1.0, 0.0);
                glVertex3f(vlx2, 1.0, vlz2);
                
                glColor4f(1.0, 1.0, 1.0, 1.0);
                
            glEnd();
            glEnable(GL_DEPTH_TEST);

        glPopMatrix();
        
        // Podpis
        
        Printer::surfacePrint(Vector3(0.0, -this->y, 0.0), this->description, 10, true);
        
        
    glPopMatrix();
    
}

void SceneObjectShip::setDescription(string desc) {
    this->description = desc;
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