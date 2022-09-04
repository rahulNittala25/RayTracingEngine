#ifndef CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER

#include <rt/integrators/integrator.h>

namespace rt {

class RecursiveRayTracingIntegrator : public Integrator {
public:
    RecursiveRayTracingIntegrator(World* world) : Integrator(world) {}
    RGBColor radiance(const Ray& ray, int count) const;
    virtual RGBColor getRadiance(const Ray& ray) const;
private:
    float offset =  0.0001f;

};

}

#endif
