#ifndef CG1RAYTRACER_LIGHTS_DIRECTIONAL_HEADER
#define CG1RAYTRACER_LIGHTS_DIRECTIONAL_HEADER

#include <rt/lights/light.h>
#include <core/color.h>

namespace rt {

class DirectionalLight : public Light {
public:
	Vector light_dir;
	RGBColor light_color;
	DirectionalLight() {}
	DirectionalLight(const Vector& direction, const RGBColor& color);
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif
