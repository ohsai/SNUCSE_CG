#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#include <iostream>

class vector{
    public:
        float coord[3];
        vector(float coord[3]);
        vector();
        vector(const vector& v2);
        float norm();
        vector operator-();
        bool isparallel(vector v2);
};


class v_n : public vector{
    public:
        float normal[3];
        v_n(float coord[3], float normal[3]);
        v_n();
        v_n(const v_n& vn2);
        v_n(vector v_in, vector normal);
};

float operator&(const vector& v1, const vector& v2); //dot prod
vector operator+(const vector& v1, const vector& v2); //add
vector operator%(const vector& v1, const vector& v2); //cross prod
vector operator*(const float& f1, const vector& v2); //scalar mult
vector operator-(const vector& v1, const vector& v2); // position - position = vector

#endif
