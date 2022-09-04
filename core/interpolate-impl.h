#include "interpolate.h"

namespace rt {

template <typename T>
T lerp(const T& px0, const T& px1, float xPoint) {
    /* TODO */
    return(px1 * xPoint + px0 * (1 - xPoint));
}

template <typename T>
T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {
    /* TODO */
    return(a * aWeight + b * bWeight + c * (1 - aWeight - bWeight));
}

template <typename T>
T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {
    /* TODO */
    T y0 = lerp(px0y0, px1y0, xWeight);
    T y1 = lerp(px0y1, px1y1, xWeight);
    return(lerp(y0, y1, yWeight));
}

template <typename T>
T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
    const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
    float xPoint, float yPoint, float zPoint)
{
    /* TODO */
    T z0 = lerp2d(px0y0z0, px1y0z0, px0y1z0, px1y1z0, xPoint, yPoint);
    T z1 = lerp2d(px0y0z1, px1y0z1, px0y1z1, px1y1z1, xPoint, yPoint);
    return(lerp(z0, z1, zPoint));
}

}