#include <rt/materials/mirror.h>
#include <core/scalar.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa)
{
    /* TODO */
    this->eta = eta;
    this->kappa = kappa;
    e2_k2 = pow(eta, 2) + pow(kappa, 2);
}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    return(RGBColor::rep(0.0f));
}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return(RGBColor::rep(0));
}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    float r_pll_2, r_ppdlr_2;
    Vector inDir = (-outDir + 2 * dot(outDir, normal) * normal).normalize();
    float cos_theta_i = dot(normal, inDir);
    r_pll_2 = (e2_k2 * pow(cos_theta_i, 2) - 2 * eta * cos_theta_i + 1) / (e2_k2 * pow(cos_theta_i, 2) + 2 * eta * cos_theta_i + 1);
    r_ppdlr_2 = (e2_k2 - 2 * eta * cos_theta_i + pow(cos_theta_i, 2)) / (e2_k2 + 2 * eta * cos_theta_i + pow(cos_theta_i, 2));
    Material::SampleReflectance s;
    s.direction = inDir;
    s.reflectance = RGBColor::rep((r_pll_2 + r_ppdlr_2) / 2);
    return(s);
}

Material::Sampling MirrorMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

}