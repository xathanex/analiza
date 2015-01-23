#include "Water.h"
#include "Vector3.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
//------------------------------------------------------------------------------
//Water
//------------------------------------------------------------------------------

Water::Water(float e, int r) : edge(e), resolution(r+2) {
    
    float floatRes = (float)(r-1);
    this->heightMap = new Vector3*[this->resolution];
    this->normals = new Vector3*[this->resolution];
    
    
    for(int z=0; z<this->resolution; z++) {
        float zCoord = ((float)(z-1) / floatRes) * this->edge;
        this->heightMap[z] = new Vector3[this->resolution];
        this->normals[z] = new Vector3[this->resolution];
        
        for(int x=0; x<this->resolution; x++) {
            float xCoord = ((float)(x-1) / floatRes) * this->edge;
            this->heightMap[z][x].set(xCoord, 0.0, zCoord);
            this->normals[z][x].set(0.0, 1.0, 0.0);
            
        }
        
    }

    
}

void Water::addWaveSource(float x, float z, float amplitude, float waveLength, float phasingSpeed) {
    WaveSource ws = WaveSource(Vector3(x, 0.0, z), amplitude, waveLength, phasingSpeed);
    ws.calculateOffsets(this->heightMap, this->resolution);
    this->waveSources.push_back(ws);

}

float Water::calcHeight(float x, float y) {
    
    float height = 0.0;
    
    if(x<0.0 || y<0.0 || x>this->edge || y>this->edge) {
        return height;
    } else {

        Vector3 tmp;
        float dist;
        float offset;

        for (vector<WaveSource>::iterator i=this->waveSources.begin(); i!=this->waveSources.end(); i++) {
            tmp = Vector3(x, 0.0, y);
            dist = ((tmp - i->getSourcePosition()).getLength());
            dist /= i->getWaveLength();
            offset = dist - floor(dist);

            height += sin((i->getPhase() + offset) * 2* 3.1415) * i->getAmplitude();    
        }

        return height;
        
    }
}

void Water::recalculateWaves() {

    for(int z=0; z<this->resolution; z++) {
        for(int x=0; x<this->resolution; x++) {
            this->heightMap[z][x].y = 0;
        }
    }
    
    for (vector<WaveSource>::iterator i=this->waveSources.begin(); i!=this->waveSources.end(); i++) {
        
        i->recalculatePhase();
        float** offsets = i->getOffsets();
        
        for(int z=0; z<this->resolution; z++) {
            for(int x=0; x<this->resolution; x++) {

                //Tutaj do zaimplementowania algorytm
                this->heightMap[z][x].y += sin((i->getPhase() + offsets[z][x]) * 2* 3.1415) * i->getAmplitude();

            }
        }
    }
    
    this->recalculateNormals();
}


void Water::recalculateNormals() {
    
    for(int z=1; z<this->resolution-1; z++) {
        for(int x=1; x<this->resolution-1; x++) {
            
            Vector3 v1 = this->heightMap[z+1][x] - this->heightMap[z][x];
            Vector3 v2 = this->heightMap[z][x+1] - this->heightMap[z][x];
            Vector3 v3 = this->heightMap[z-1][x] - this->heightMap[z][x];
            Vector3 v4 = this->heightMap[z][x-1] - this->heightMap[z][x];
            
            normals[z][x].set(0.0, 0.0, 0.0);
            Vector3 tmp;
                    
            tmp = Vector3::crossProduct(v1, v2);
            tmp.normalize();
            normals[z][x] += tmp;
            tmp = Vector3::crossProduct(v2, v3);
            tmp.normalize();
            normals[z][x] += tmp;
            tmp = Vector3::crossProduct(v3, v4);
            tmp.normalize();
            normals[z][x] += tmp;
            tmp = Vector3::crossProduct(v4, v1);
            tmp.normalize();
            normals[z][x] += tmp;
            
            
            normals[z][x].normalize();
            
        }
    }


}


void Water::drawWaves() {
    
    
    for(int z=1; z<this->resolution-2; z++) {
        for(int x=1; x<this->resolution-2; x++) {
            glBegin(GL_POLYGON);
            
                glNormal3f(this->normals[z+1][x+1].x, this->normals[z+1][x+1].y, this->normals[z+1][x+1].z);
                glVertex3f(this->heightMap[z+1][x+1].x, this->heightMap[z+1][x+1].y, this->heightMap[z+1][x+1].z);  
                
                glNormal3f(this->normals[z][x].x, this->normals[z][x].y, this->normals[z][x].z);
                glVertex3f(this->heightMap[z][x].x, this->heightMap[z][x].y, this->heightMap[z][x].z);
                
                glNormal3f(this->normals[z+1][x].x, this->normals[z+1][x].y, this->normals[z+1][x].z);
                glVertex3f(this->heightMap[z+1][x].x, this->heightMap[z+1][x].y, this->heightMap[z+1][x].z);

                
                
                
                glNormal3f(this->normals[z+1][x].x, this->normals[z+1][x].y, this->normals[z+1][x].z);
                glVertex3f(this->heightMap[z+1][x+1].x, this->heightMap[z+1][x+1].y, this->heightMap[z+1][x+1].z);
                
                glNormal3f(this->normals[z][x+1].x, this->normals[z][x+1].y, this->normals[z][x+1].z);
                glVertex3f(this->heightMap[z][x+1].x, this->heightMap[z][x+1].y, this->heightMap[z][x+1].z);
                
                glNormal3f(this->normals[z][x].x, this->normals[z][x].y, this->normals[z][x].z);
                glVertex3f(this->heightMap[z][x].x, this->heightMap[z][x].y, this->heightMap[z][x].z);
                
            glEnd();  
        }
    }
    
   
    
}


Water::~Water() {
    delete[] this->heightMap;
    delete[] this->normals;
    
    for (vector<WaveSource>::iterator i=this->waveSources.begin(); i!=this->waveSources.end(); i++) {
        i->deleteOffsets();
    }
    
}

//------------------------------------------------------------------------------
//WaveSource
//------------------------------------------------------------------------------

Water::WaveSource::WaveSource(Vector3 sourcePosition, float amplitude, float waveLength, float phasingSpeed) {

    this->sourcePosition = sourcePosition;
    this->amplitude = amplitude;
    this->waveLength = waveLength;
    this->phasingSpeed = phasingSpeed;
    
    this->phase = 0.0;
    
}


void Water::WaveSource::recalculatePhase() {
    this->phase += this->phasingSpeed;
    if(this->phase > 1.0) {
        this->phase -= 1.0;
    }
    
}


void Water::WaveSource::calculateOffsets(Vector3** heightMap, int resolution) {
    
    float dist;
    Vector3 tmp;
    this->offsets = new float*[resolution];
    for(int z=0; z<resolution; z++) {
        this->offsets[z] = new float[resolution];
        for(int x=0; x<resolution; x++) {
            tmp = heightMap[z][x];
            tmp.set(tmp.x, 0.0, tmp.z);
            dist = ((tmp - this->sourcePosition).getLength());
            dist /= this->waveLength;
            this->offsets[z][x] = dist - floor(dist);
            
        }
        
    }
      
} 

float** Water::WaveSource::getOffsets() {
    return this->offsets;
}

float Water::WaveSource::getPhase() {
    return this->phase;
}
  
float Water::WaveSource::getAmplitude() {
    return this->amplitude;
}

float Water::WaveSource::getWaveLength() {
    return this->waveLength;
}

void Water::WaveSource::deleteOffsets() {
    delete[] this->offsets;
}

Vector3 Water::WaveSource::getSourcePosition() {
    return this->sourcePosition;
}

Water::WaveSource::~WaveSource() {}