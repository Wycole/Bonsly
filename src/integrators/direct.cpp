#include <lightwave.hpp>

namespace lightwave {

class DirectIntegrator : public SamplingIntegrator {

public:
    DirectIntegrator(const Properties &properties)
        : SamplingIntegrator(properties) {}

    Color Li(const Ray &ray, Sampler &rng) override {

        Intersection its = m_scene->intersect(ray, rng);
        Color output;

        if (!its) {                              // no surface intersection
            return its.evaluateEmission().value; // background color
        }

        // surface intersection occurs
        LightSample isik = m_scene->sampleLight(rng); // light sample

        if (!isik) {
            return Color(1.0);
        }

        DirectLightSample directlight =
            isik.light->sampleDirect(its.position, rng);

        // take the light sample at the point of intersectiondire (part d)
        Ray secondary_ray = Ray(its.position, directlight.wi, ray.depth + 1);
        Intersection its2 = m_scene->intersect(secondary_ray, rng);

        if (!its2 || (its2.t > directlight.distance)) {
            // no intersection, or behind the light sourse
            // light is not occluded (visible)
            // Evaluate BSDF at the hit point for the light direction
            Color bsdfVal           = its.evaluateBsdf(directlight.wi).value;
            Color lightContribution = directlight.weight * bsdfVal;

            // Account for the light sampling probability
            lightContribution = lightContribution / isik.probability;

            // accumulating contributions
            output += lightContribution;
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
