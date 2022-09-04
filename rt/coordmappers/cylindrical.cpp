#include <rt/coordmappers/cylindrical.h>
#include <rt/intersection.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
{
    this->origin = origin;
    this->longitudinalAxis = longitudinalAxis;
    this->polarAxis = polarAxis - dot(polarAxis, longitudinalAxis.normalize()) * longitudinalAxis;
    this->polarPerpAxis = cross(longitudinalAxis, this->polarAxis).normalize();
    this->scaleY = this->longitudinalAxis.length();
    this->scaleX = this->polarAxis.length();
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    Vector point = hit.local() - origin;
    float v = dot(longitudinalAxis, point)/(scaleY*scaleY);
    Vector polarPlaneHit = point - v * longitudinalAxis;
    float u1, u2;
    u2 = dot(polarPlaneHit, polarPerpAxis);
    u1 = acos(dot(polarAxis.normalize(), polarPlaneHit.normalize()));
    if (u2 < 0) {
        return(Point(u1 / (2 * pi * scaleX), v, 0));
    }
    return(Point((1/scaleX)- (u1 / (2 * pi * scaleX)), v, 0));
}

}