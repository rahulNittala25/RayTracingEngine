#include <rt/coordmappers/spherical.h>
#include <rt/intersection.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this->origin = origin;
    this->zenith = zenith;
    this->scaleZenith = zenith.length();
    this->azimuthRef = azimuthRef - dot(azimuthRef, this->zenith.normalize())*zenith;
    this->scaleAzimuthRef = this->azimuthRef.length();
    this->perpDirection = cross(this->zenith, this->azimuthRef).normalize();
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    Vector point = hit.local() - origin;
    float v = acos(dot(zenith.normalize(), point.normalize()))/(pi*scaleZenith);
    Vector azimuthPlaneHit = point - zenith * dot(zenith, point) / (scaleZenith * scaleZenith);
    float u1, u2;
    u2 = dot(azimuthPlaneHit, perpDirection);
    u1 = acos(dot(azimuthRef.normalize(), azimuthPlaneHit.normalize()));
    if (u2 < 0) {
        return(Point(u1 / (2 * pi * scaleAzimuthRef), v, 0));
    }
    return(Point((1 / scaleAzimuthRef) - (u1 / (2 * pi * scaleAzimuthRef)), v, 0));
}

}
