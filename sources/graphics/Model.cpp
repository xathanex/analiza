#include "Model.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

Model::Model() {}

void Model::addVertex(Vector3 vert) {
    this->vertices.push_back(vert);
}

void Model::addNormal(Vector3 normal) {
    this->normals.push_back(normal);
}

void Model::addFace(int v1, int v2, int v3, int n1, int n2, int n3) {
    this->faceVerts.push_back(v1);
    this->faceVerts.push_back(v2);
    this->faceVerts.push_back(v3);
    
    this->faceNormals.push_back(n1);
    this->faceNormals.push_back(n2);
    this->faceNormals.push_back(n3);
    
}

void Model::draw() {
    
    
    for(int i=0; i<this->faceVerts.size(); i+=3) {
        glBegin(GL_TRIANGLES);
        for(int f=i; f<i+3; f++) {
            int v = this->faceVerts[f]-1;
            int n = this->faceNormals[f]-1;
            glNormal3f(this->normals[n].x, this->normals[n].y, this->normals[n].z);
            glVertex3f(this->vertices[v].x, this->vertices[v].y, this->vertices[v].z);
        }
        glEnd();
    }
    


}


Model::~Model() {}

