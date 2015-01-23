#ifndef SCENE_H
#define	SCENE_H

#include "Water.h"
#include "SceneObjects.h"

class Scene {
public:
    Scene();
    virtual ~Scene();
    
    void registerSceneObject(SceneObject* sceneObject);
    void unregisterSceneObject(SceneObject* sceneObject);
    
    static Water* water;
    
private:
    vector<SceneObject*> sceneObjects;
    
    void glInit();
    void setLights();
    void display();
    void run();
    

    
};


#endif	/* SCENE_H */



