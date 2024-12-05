#include <lightwave.hpp>

namespace lightwave {

class Diffuse : public Bsdf {
    ref<Texture> m_albedo;

public:
    Diffuse(const Properties &properties) {
        m_albedo = properties.get<Texture>("albedo");
    }

    BsdfEval evaluate(const Point2 &uv, const Vector &wo,
                      const Vector &wi) const override {
        return { m_albedo->evaluate(uv) * Frame::absCosTheta(wi) * InvPi };
        // this is the frfr * |cosD|
    }

    BsdfSample sample(const Point2 &uv, const Vector &wo,
                      Sampler &rng) const override {
        // vector v is the reflected vectore from the diffuse area
        Vector v = squareToCosineHemisphere(rng.next2D());
        return BsdfSample{ v.normalized(), m_albedo->evaluate(uv) };
    }

    std::string toString() const override {
        return tfm::format(
            "Diffuse[\n"
            "  albedo = %s\n"
            "]",
            indent(m_albedo));
    }
};

} // namespace lightwave

REGISTER_BSDF(Diffuse, "diffuse")
