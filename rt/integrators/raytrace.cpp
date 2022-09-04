#include <rt/integrators/raytrace.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/materials/material.h>
#include <rt/solids/solid.h>
#include <rt/coordmappers/coordmapper.h>

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    Intersection hit_point = this->world->scene->intersect(ray);
    if (hit_point) {
        Point local_hit = hit_point.solid->texMapper->getCoords(hit_point);
        RGBColor color = hit_point.solid->material->getEmission(local_hit, hit_point.normal(), -ray.d);
        for (int i = 0; i < world->light.size(); i++) {
            LightHit light_hit = world->light[i]->getLightHit(hit_point.hitPoint());
            if (dot(light_hit.direction, hit_point.normal()) < epsilon) {
                continue;
            }
            Intersection obstruction_hit = this->world->scene->intersect(Ray(hit_point.hitPoint(), light_hit.direction));
            if(obstruction_hit) {
                if (obstruction_hit.distance < light_hit.distance) {
                    continue;
                }
            }
            color = color + (this->world->light[i]->getIntensity(light_hit) * hit_point.solid->material->getReflectance(local_hit, hit_point.normal(), -ray.d, light_hit.direction));
        }
        return(color);
    }
    return(RGBColor::rep(0.0f));
}

}