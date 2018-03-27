#include <math.h>

struct Interval {
    float x, y;
}

double calcDistance(float x1, float y1, float x2, float y2) {
    return sqrt( pow(x1 - y1, 2) + pow(x2 - y2, 2) );
}
