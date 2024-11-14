#include <lightwave.hpp>

namespace lightwave {

class DirectIntegrator : public SamplingIntegrator {

public:
    DirectIntegrator(const Properties &properties)
        : SamplingIntegrator(properties) {}

    Color Li(const Ray &ray, Sampler &rng) override {
        Intersection its = m_scene->intersect(ray, rng);
        Color output;
        if (!its) {
            return its.evaluateEmission().value; // no intersection background
        } else {
            LightSample isik = m_scene->sampleLight(rng); // light sample
            DirectLightSample directlight =
                isik.light->sampleDirect(its.position, rng);
            // take the light sample at the point
            // of intersectiondire
            Ray secondary_ray = Ray(its.position, directlight.wi, 1);
            Intersection its2 = m_scene->intersect(secondary_ray, rng);
            if (!its2 || ((its2.t) > directlight.distance)) {
                output = directlight.weight *
                         its.evaluateBsdf(directlight.wi).value *
                         max(its.shadingNormal.dot(directlight.wi), 0.f);
            }
        }
        return output;
    }

    std::string toString() const override {
        return tfm::format(
            "DirectIntegrator[\n"
            "  sampler = %s,\n"
            "  image = %s,\n"
            "]",
            indent(m_sampler),
            indent(m_image));
    }
};

} // namespace lightwave

REGISTER_INTEGRATOR(DirectIntegrator, "direct")
