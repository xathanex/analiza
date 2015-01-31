#include "AssetLoader.h"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Vector3.h"

using namespace std;

vector<Model> AssetLoader::models;
vector<int> AssetLoader::textures;

int AssetLoader::loadModel(string modelFile) {
    string parsedLine;

    ifstream file(modelFile.c_str());
    Model model = Model();
    
    if(file.is_open()) {
        while(getline(file, parsedLine)) {
            stringstream tmp(parsedLine);
            string parsedFraze;
            
            if(parsedLine.substr(0, 2) == "v ") {
                float c[3];
                for(int i=0; i<4; i++) {
                    getline(tmp, parsedFraze, ' ');
                    if(i>0)
                        c[i-1] = atof(parsedFraze.c_str());
                }
                Vector3 v = Vector3(c[0], c[1], c[2]);
                model.addVertex(v);
                
            } else if(parsedLine.substr(0, 2) == "vn") {
                float c[3];
                for(int i=0; i<4; i++) {
                    getline(tmp, parsedFraze, ' ');
                    if(i>0)
                        c[i-1] = atof(parsedFraze.c_str());
                }
                Vector3 n = Vector3(c[0], c[1], c[2]);
                model.addNormal(n);
                
            } else if(parsedLine.substr(0, 2) == "f ") {
                
                int v[3];
                int n[3];
                for(int i=0; i<4; i++) {
                    getline(tmp, parsedFraze, ' ');
                    if(i>0) {
                        size_t delimiterPos = parsedFraze.find("//");
                        v[i-1] = atoi(parsedFraze.substr(0, delimiterPos).c_str());
                        n[i-1] = atoi(parsedFraze.substr(delimiterPos+2, parsedFraze.length()-(delimiterPos+2)).c_str());
                    }
                    
                }
                model.addFace(v[0], v[1], v[2], n[0], n[1], n[2]);
                
            }
            
        }
        
        AssetLoader::models.push_back(model);
        
    } else {
        cout<<"err";
        file.close();
    }
    return AssetLoader::models.size()-1;
}

int AssetLoader::loadTexture(const char* file) {
    
        SDL_Surface* img = SDL_LoadBMP(file);
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(img);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        AssetLoader::textures.push_back(id);
        return id;
        
}


AssetLoader::AssetLoader() {}
AssetLoader::~AssetLoader() {}

