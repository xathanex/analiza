#include "Scene.h"
#include <iostream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <thread>

#include "Water.h"
#include "AssetLoader.h"


using namespace std;

Water* Scene::water = nullptr;

void Scene::glInit()
{
    glClearColor(0.9, 0.9, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,1200.0/700.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    
    float fogColor[4] = {0.9, 0.9, 0.9, 1.0};
    glEnable (GL_FOG);
    glFogi (GL_FOG_MODE, GL_LINEAR);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, 0.3);
    
    glFogf(GL_FOG_START, 1.0);
    glFogf(GL_FOG_END, 30.0);
    
    
    glHint (GL_FOG_HINT, GL_NICEST);
    
    glLoadIdentity();
}

void Scene::display() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glRotatef(45, 1, 0, 0);
    glTranslatef(-12.0, 0-10.0, -25.0);
    Scene::water->drawWaves();
    for (vector<SceneObject*>::iterator i=this->sceneObjects.begin(); i!=this->sceneObjects.end(); i++) {
        (*i)->draw();
    }
    
}

void Scene::setLights() {
    glEnable(GL_LIGHT0);
    float lightDirection[4] = {0.2, 0.5, 0.2, 0.0};
    float diffuse[3] = {1.0, 1.0, 1.0};
    float ambient[3] = {0.5, 0.5, 0.5};
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    

}

void Scene::run() {

    Uint32 start;
    bool running=true;
    SDL_Event event;
    
    while(running) {

        Scene::water->recalculateWaves();
        
        start=SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            switch(event.type)
            {
            case SDL_QUIT:
            running=false;
            break;
            }
        }
        
        this->display();
        SDL_GL_SwapBuffers();
        
        
        if(1000/30>(SDL_GetTicks()-start)) {
            SDL_Delay(1000/30-(SDL_GetTicks()-start));
        }
        
        
    }
    
    SDL_Quit();
    
}

Scene::Scene() {

    //Inicjalizacja -------- ---------------------------------------------------
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen=SDL_SetVideoMode(1200,700,32,SDL_SWSURFACE|SDL_OPENGL);
    this->glInit();
    this->setLights();
    
    
    //Tworzenie wody -----------------------------------------------------------
    Scene::water = new Water(24.0, 30);
    Scene::water->addWaveSource(-200.0, -200.0, 0.2, 4.0, 0.01);
    Scene::water->addWaveSource(100.0, 20.0, 0.04, 1.0, 0.02);
    Scene::water->addWaveSource(50.0, 0.0, 0.07, 1.2, 0.015);

    //Wczytywanie assetów ------------------------------------------------------
    AssetLoader::loadModel("graphics/meshes/ship.obj");
    AssetLoader::loadModel("graphics/meshes/cannon.obj");
    AssetLoader::loadModel("graphics/meshes/projectile.obj");
    
    //Uruchamianie wątku -------------------------------------------------------
    
    //thread renderer(&Scene::run, this);
    
    SceneObjectShip* ship1 = new SceneObjectShip();
    ship1->setPosition(400, 400);
    ship1->setDirection(-1.0, -1.0);
    ship1->setCannonDirection(-1.0, -1.0); 
    this->registerSceneObject(ship1);   
    
    SceneObjectShip* ship2 = new SceneObjectShip();
    ship2->setPosition(500, 300);
    ship2->setDirection(1.0, 1.0);
    ship2->setCannonDirection(0.0, 1.0); 
    this->registerSceneObject(ship2);   

    SceneObjectShip* ship3 = new SceneObjectShip();
    ship3->setPosition(200, 200);
    ship3->setDirection(1.0, 0.4);
    ship3->setCannonDirection(0.0, 1.0); 
    this->registerSceneObject(ship3);   
    
    this->run();
    
}

void Scene::registerSceneObject (SceneObject* sceneObject) {
    this->sceneObjects.push_back(sceneObject);
}
void Scene::unregisterSceneObject (SceneObject* sceneObject) {
    vector<SceneObject*>::iterator toDelete;
    for (vector<SceneObject*>::iterator i=this->sceneObjects.begin(); i!=this->sceneObjects.end(); i++) {
        if ((*i)==sceneObject) {
            toDelete = i;
        }
    }
    this->sceneObjects.erase(toDelete);
}

Scene::~Scene() {
    delete(Scene::water);
}

