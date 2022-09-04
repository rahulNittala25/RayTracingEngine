#include <rt/cameras/perspective.h>
#include <math.h>
#include <core/random.h>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float time0, float time1)
{
    this->center = center;
  	this->forward = forward;
  	this->up = up;
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;

    this->scaleX = tan(this->horizontalOpeningAngle/2.0f);
    this->scaleY = tan(this->verticalOpeningAngle/2.0f);

    this->CamZAxis = this->forward.normalize();
    this->CamXAxis = cross(this->forward, this->up.normalize()).normalize();
    this->CamYAxis = cross(this->CamXAxis, this->CamZAxis).normalize();

    this->time0 = time0;
    this->time1 = time1;
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
		Vector dir = (x * CamXAxis * scaleX + y * CamYAxis * scaleY +  CamZAxis).normalize();
    float t = time0 + random() * (time1 - time0);
		return Ray(center, dir, t);
}

}
