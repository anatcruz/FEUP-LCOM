#include "vector2.h"
#include <math.h>

vector2 vector2_add(vector2 v1, vector2 v2) {
     vector2 res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    
    return res;
}

vector2 vector2_subtract(vector2 v1, vector2 v2) {
    vector2 res;

    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    
    return res;
}

vector2 vector2_scalar_product(vector2 v, float k) {
    vector2 res;

    res.x = v.x * k;
    res.y = v.y * k;
    
    return res;
}

float vector2_norm(vector2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

vector2 vector2_normalized(vector2 v) {
    float norm = vector2_norm(v);

    v.x /= norm;
    v.y /= norm;

    return v;
}
