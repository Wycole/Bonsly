#include "fresnel.hpp"
#include "microfacet.hpp"
#include <lightwave.hpp>

namespace lightwave {

class RoughDielectric : public Bsdf {

    ref<Texture> m_ior;
    ref<Texture> m_reflectance;
    ref<Texture> m_transmittance;
    ref<Texture> m_roughness;

public:
    RoughDielectric(const Properties &properties) {
        m_ior           = properties.get<Texture>("ior");
        m_reflectance   = properties.get<Texture>("reflectance");
        m_transmittance = properties.get<Texture>("transmittance");
        m_roughness     = properties.get<Texture>("roughness");
    }

    BsdfEval evaluate(const Point2 &uv, const Vector &wo,
                      const Vector &wi) const override {

        // // everything from rough conductor
        // const auto alpha = std::max(float(1e-3),
        // sqr(m_roughness->scalar(uv)));

        // Color reflectance = m_reflectance->evaluate(uv);

        // Vector w_m  = (wi + wo) / (wi + wo).length(); // the halfvector
        // float d_wm  = microfacet::evaluateGGX(alpha, w_m);
        // float g1_wi = microfacet::smithG1(alpha, w_m, wi);
        // float g1_wo = microfacet::smithG1(alpha, w_m, wo);

        // float denominator =
        //     1 / abs(4 * Frame::cosTheta(wo)); // why not the one below?
        // // float demoninator =
        // //     1 / abs(4 * Frame::cosTheta(wo) * Frame::cosTheta(wi));

        // Color together = reflectance * d_wm * g1_wi * g1_wo * denominator;

        // return BsdfEval{ together };
        const auto alpha = std::max(float(1e-3), sqr(m_roughness->scalar(uv)));
        float ior        = m_ior->scalar(uv);
        Vector ht;
        bool reflect = Frame::sameHemisphere(wo, wi);

        if (reflect) {
            ht = (wi + wo).normalized();
        } else {
            ht = (wi + wo * ior).normalized();
        }

        float F = fresnelDielectric(wi.dot(ht), ior);
        // float F = fresnelDielectric(Frame::cosTheta(wo), ior); old version
        float g1_wi = microfacet::smithG1(alpha, ht, wi);
        float g1_wo = microfacet::smithG1(alpha, ht, wo);
        float d_wm  = microfacet::evaluateGGX(alpha, ht);

        if (reflect) {
            float value =
                g1_wi * g1_wo * F * d_wm / (4 * Frame::absCosTheta(wo));
            return BsdfEval{ value * m_reflectance->evaluate(uv) };
        } else {
            float fraction = wi.dot(ht) + ior * wo.dot(ht);
            float value    = g1_wi * g1_wo * (1 - F) * d_wm * ior * ior *
                          abs(wi.dot(ht)) * abs(wo.dot(ht)) /
                          abs(Frame::cosTheta(wo) * fraction * fraction);
            return BsdfEval{ value * m_transmittance->evaluate(uv) };
        }
    }

    BsdfSample sample(const Point2 &uv, const Vector &wo,
                      Sampler &rng) const override {

        // float ior = m_ior->scalar(uv);
        // // Vector normal = Vector(0, 0, 1);

        // const auto alpha = std::max(float(1e-3),
        // sqr(m_roughness->scalar(uv))); Vector normal    =
        // microfacet::sampleGGXVNDF(alpha, wo, rng.next2D());

        // // from dielectric
        // if (Frame::cosTheta(wo) < 0) {
        //     if (ior != 0) {
        //         ior    = 1 / ior;
        //         normal = -normal;
        //     }
        // }
        // // fresnel coefficients
        // // float F = fresnelDielectric(normal.dot(wo), ior);
        // float F = fresnelDielectric(wo.z(), ior);

        // // reflect
        // if (rng.next() < F) {
        //     Vector wi = reflect(wo, normal);
        //     return BsdfSample{ wi, m_reflectance->evaluate(uv) };
        // }

        // // refractence / transmittance
        // // refract wo around the normal
        // Vector wi = refract(wo, normal, ior);

        // // checking if a zero vector was returned
        // if (wi.isZero()) {
        //     // if refraction fails, fallback to reflection
        //     wi = reflect(wo, normal);
        //     return BsdfSample{ wi, m_reflectance->evaluate(uv) };
        // }

        // float g1     = microfacet::smithG1(alpha, normal, wi);
        // Color weight = (m_transmittance->evaluate(uv) / (ior * ior)) * g1;

        // return BsdfSample{ wi, weight };
        float ior        = m_ior->scalar(uv);
        const auto alpha = std::max(float(1e-3), sqr(m_roughness->scalar(uv)));
        Vector normal    = microfacet::sampleGGXVNDF(alpha, wo, rng.next2D());
        // if the ray is entering the medium, we need to flip the ior and the
        // normal
        if (Frame::cosTheta(wo) < 0) {
            ior = 1 / ior;
        }
        // calculate the fresnel coefficients
        float F = fresnelDielectric(normal.dot(wo), ior);

        // reflectance
        if (rng.next() < F) {
            Vector wi    = reflect(wo, normal);
            float g1     = microfacet::smithG1(alpha, normal, wi);
            Color weight = m_reflectance->evaluate(uv) * g1;
            return BsdfSample{ wi, weight };
        }
        // transmittance
        Vector wi    = refract(wo, normal, ior);
        float g1     = microfacet::smithG1(alpha, normal, wi);
        Color weight = (m_transmittance->evaluate(uv) / (ior * ior)) * g1;
        return BsdfSample{ wi, weight };
    }

    std::string toString() const override {
        return tfm::format(
            "RoughDielectric[\n"
            "  ior           = %s,\n"
            "  reflectance   = %s,\n"
            "  transmittance = %s\n"
            "  roughness = %s\n"
            "]",
            indent(m_reflectance),
            indent(m_roughness));
    }
};

} // namespace lightwave

REGISTER_BSDF(RoughDielectric, "roughdielectric")