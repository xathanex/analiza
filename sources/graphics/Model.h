#ifndef MODEL_H
#define	MODEL_H
#include <vector>
#include "Vector3.h"

using namespace std;

class Model {
public:
    Model();
    virtual ~Model();
    
    void addVertex(Vector3 vert);
    void addNormal(Vector3 normal);
    void addFace(int vert1, int vert2, int vert3, int normal1, int normal2m, int normal3);
    void draw();
    
private:
    vector<Vector3> vertices;
    vector<Vector3> normals;
    
    vector<int> faceVerts;
    vector<int> faceNormals;
    
};

#endif	/* MODEL_H */

