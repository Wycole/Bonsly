#include <lightwave.hpp>

namespace lightwave {

class DirectIntegrator : public SamplingIntegrator {

public:
    DirectIntegrator(const Properties &properties)
        : SamplingIntegrator(properties) {}

    Color Li(const Ray &ray, Sampler &rng) override {

        Intersection its = m_scene->intersect(ray, rng);
        Color output;

        if (!its) { // no surface intersection
            // part a

            return its.evaluateEmission().value; // no intersection background
            // part b
        }
        // surface intersection occurs
        LightSample isik = m_scene->sampleLight(rng); // light sample
        DirectLightSample directlight =
            isik.light->sampleDirect(its.position, rng);
        // take the light sample at the point
        // of intersectiondire
        // part d
        Ray secondary_ray = Ray(its.position, directlight.wi, ray.depth + 1);
        Intersection its2 = m_scene->intersect(secondary_ray, rng);
        if (!its2 || (its2.t > directlight.distance)) {
            // no intersection, or behind the light source
            // light is not occluded
            output = directlight.weight *
                     its.evaluateBsdf(directlight.wi).value *
                     max(0.f, abs(its.shadingNormal.dot(directlight.wi)));
            // taking the absolute value and its fine now
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
