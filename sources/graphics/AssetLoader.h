#ifndef ASSETLOADER_H
#define	ASSETLOADER_H
#include <string>
#include <vector>
#include "Model.h"

using namespace std;

class AssetLoader {
public:
    AssetLoader();
    virtual ~AssetLoader();
    
    static int loadModel(string modelFile);
    static int loadTexture(const char* textureFile);
    static vector<Model> models;
    static vector<int> textures;
    
private:

};

#endif	/* ASSETLOADER_H */

