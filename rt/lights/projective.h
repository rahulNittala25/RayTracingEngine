#ifndef CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER

#include <core/point.h>
#include <core/color.h>
#include <rt/lights/light.h>
#include <rt/ray.h>

#include <rt/renderer.h>
#include <core/julia.h>

namespace rt {

class ProjectiveLight : public Light {
public:
	Point light_position;
	RGBColor light_intensity;
	ProjectiveLight() {}
	ProjectiveLight(const Point& position, const RGBColor& intensity);
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif
