#include <lightwave.hpp>

namespace lightwave {

class Lambertian : public Emission {
    ref<Texture> m_emission;

public:
    Lambertian(const Properties &properties) {
        m_emission = properties.get<Texture>("emission");
    }

    EmissionEval evaluate(const Point2 &uv, const Vector &wo) const override {
        // NOT_IMPLEMENTED
        Color c;
        if (Frame::cosTheta(wo) < 0) {
            c = Color::black();
        } else {
            c = m_emission->evaluate(uv);
        }

        return EmissionEval{ c };
    }

    std::string toString() const override {
        return tfm::format(
            "Lambertian[\n"
            "  emission = %s\n"
            "]",
            indent(m_emission));
    }
};

} // namespace lightwave

REGISTER_EMISSION(Lambertian, "lambertian")
