#include <rt/materials/fuzzymirror.h>
#include <rt/solids/disc.h>

namespace rt {

FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
{
    this->eta = eta;
    this->kappa = kappa;
    this->fuzzyangle = fuzzyangle;
    this->e2_k2 = pow(eta, 2) + pow(kappa, 2);
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    return(RGBColor::rep(0.0f));
}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return(RGBColor::rep(0.0f));
}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    float r_pll_2, r_ppdlr_2;
    Vector reflDir = (-outDir + 2 * dot(outDir, normal) * normal).normalize();
    Disc d = Disc(texPoint + reflDir, reflDir, tan(fuzzyangle), nullptr, nullptr);
    Vector inDir = (d.sample().point - texPoint).normalize();
    float cos_theta_i = dot(normal, inDir);
    r_pll_2 = (e2_k2 * pow(cos_theta_i, 2) - 2 * eta * cos_theta_i + 1) / (e2_k2 * pow(cos_theta_i, 2) + 2 * eta * cos_theta_i + 1);
    r_ppdlr_2 = (e2_k2 - 2 * eta * cos_theta_i + pow(cos_theta_i, 2)) / (e2_k2 + 2 * eta * cos_theta_i + pow(cos_theta_i, 2));
    Material::SampleReflectance s;
    s.direction = inDir;
    s.reflectance = RGBColor::rep((r_pll_2 + r_ppdlr_2) / 2);
    return(s);
}

Material::Sampling FuzzyMirrorMaterial::useSampling() const {
    /* TODO */
    return SAMPLING_ALL;
}

}
