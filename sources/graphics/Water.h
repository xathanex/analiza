#ifndef WATER_H
#define	WATER_H

#include <vector>
#include "Vector3.h"

using namespace std;

class Water {

    class WaveSource {
        public:
            WaveSource(Vector3 sourcePosition, float amplitude, float waveLength, float phasingSpeed);
            virtual ~WaveSource();
            
            void recalculatePhase();
            float getPhase();
            float getAmplitude();
            float getWaveLength();
            Vector3 getSourcePosition();
            
            void calculateOffsets(Vector3**, int resolution);
            float** getOffsets();
            void deleteOffsets();
            
        private:
            float amplitude, waveLength, phasingSpeed;
            Vector3 sourcePosition;
            float phase;
            float** offsets;
            
    };

    
    public:
        Water(float edge, int resolution);
        virtual ~Water();

        void recalculateWaves();
        void recalculateNormals();
        void drawWaves();
        void addWaveSource(float x, float z, float amplitude, float waveLength, float phasingSpeed);
        float calcHeight(float x, float y);
        float edge;
        
    private:
        int resolution;
        Vector3** heightMap;
        Vector3** normals;
        vector<WaveSource> waveSources;

};



#endif	/* WATER_H */

