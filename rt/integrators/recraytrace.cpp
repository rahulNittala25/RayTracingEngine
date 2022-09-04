#include <rt/integrators/recraytrace.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/materials/material.h>
#include <rt/solids/solid.h>
#include <rt/coordmappers/coordmapper.h>
#include <core/random.h>

namespace rt {

    RGBColor RecursiveRayTracingIntegrator::radiance(const Ray& ray, int count) const {
        if (count >= 30) {
            return(RGBColor::rep(0));
        }
        Intersection hit_point = this->world->scene->intersect(ray);
        if (hit_point) {
            Point local_hit = hit_point.solid->texMapper->getCoords(hit_point);
            RGBColor color = hit_point.solid->material->getEmission(local_hit, hit_point.normal(), -ray.d);
            Material::Sampling sample = hit_point.solid->material->useSampling();
            if (sample == Material::Sampling::SAMPLING_ALL || sample == Material::Sampling::SAMPLING_SECONDARY) {
                Material::SampleReflectance sample_reflect = hit_point.solid->material->getSampleReflectance(local_hit, hit_point.normal(), -ray.d);
                color = color + sample_reflect.reflectance * radiance(Ray(hit_point.hitPoint() + sample_reflect.direction * offset, sample_reflect.direction, hit_point.ray.t), count + 1);
            }
            if (sample == Material::Sampling::SAMPLING_NOT_NEEDED || sample == Material::Sampling::SAMPLING_SECONDARY) {

                for (int i = 0; i < world->light.size(); i++) {
                    LightHit light_hit = world->light[i]->getLightHit(hit_point.hitPoint());
                    if (dot(light_hit.direction, hit_point.normal()) < epsilon) {
                        continue;
                    }
                    Intersection obstruction_hit = this->world->scene->intersect(Ray(hit_point.hitPoint(), light_hit.direction, hit_point.ray.t));
                    if (obstruction_hit) {
                        if (obstruction_hit.distance < light_hit.distance) {
                            if (!obstruction_hit.solid->material->isGlass && random()<0.5) {
                                continue;
                            }
                        }
                    }
                    color = color + (this->world->light[i]->getIntensity(light_hit) * hit_point.solid->material->getReflectance(local_hit, hit_point.normal(), -ray.d, light_hit.direction));
                }

            }
            return(color);
        }
        return(RGBColor::rep(0.0f));
    }

    RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
        /* TODO */
        return(radiance(ray, 0));
    }

}
