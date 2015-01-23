#ifndef VECTOR_H
#define	VECTOR_H

class Vector3 {
    public:
        Vector3();
        Vector3(float x, float y, float z);
        virtual ~Vector3();

        Vector3 operator +(const Vector3 &v);
        Vector3 operator -(const Vector3 &v);
        Vector3 operator +=(const Vector3 &v);

        float getLength();
        void normalize();
        void set(float x, float y, float z);
        static Vector3 crossProduct(Vector3 v1, Vector3 v2);
        static float getEulerAngles(Vector3 v1);
        float x, y, z;

    private:

};

#endif	/* VECTOR_H */

