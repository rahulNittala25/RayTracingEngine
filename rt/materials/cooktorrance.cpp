#include <rt/materials/cooktorrance.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/scalar.h>
#include <math.h>
#include <vector>

namespace rt {

CookTorranceMaterial::CookTorranceMaterial(Texture* texture, float kd, float fs, float r) {
    this->kd = kd;
    this->fs = fs;
    this->r = r;
    this->texture = texture;
}

RGBColor CookTorranceMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    Vector n = normal.normalize();
    Vector h = (inDir + outDir).normalize();

    RGBColor color = RGBColor::rep(0.0f);
    color = color + kd * (texture->getColor(texPoint) * dot(inDir.normalize(), normal) / pi);

    float NI = dot(normal, inDir);
    float NH = dot(normal, h);
    float NO = dot(normal, outDir);
    float OH = dot(outDir, h);

    // Shlick
    float F = fs + (1 - fs) * powf((1 - OH), 5);

    // Beckmann
    float D = (1.0f / (pi * r * r * powf(NH, 4))) * exp((NH * NH - 1) / (NH * NH * r * r));

    // Geometric
    float G = std::min(1.0f, std::min((2 * NH * NO / OH), (2 * NH * NI / OH)));

    // Cook Torrance
    float spec = F * D * G / (pi * NI * NO);

    color = color + ((1 - kd) * texture->getColor(texPoint) * NI * spec);
    return color;
}

RGBColor CookTorranceMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor(0, 0, 0);
}

Material::SampleReflectance CookTorranceMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return Material::SampleReflectance();
}

Material::Sampling CookTorranceMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}
