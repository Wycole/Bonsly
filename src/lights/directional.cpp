#include <lightwave.hpp>

namespace lightwave {

class DirectionalLight final : public Light {
    Vector direction;
    Color power;

public:
    DirectionalLight(const Properties &properties) : Light(properties) {
        direction = properties.get<Vector>("direction");
        power     = properties.get<Color>("intensity");
    }

    DirectLightSample sampleDirect(const Point &origin,
                                   Sampler &rng) const override {
        Vector wi    = direction;
        Color weight = power;
        return DirectLightSample{ direction.normalized(), weight, Infinity };
    }

    bool canBeIntersected() const override { return false; }

    std::string toString() const override {
        return tfm::format(
            "DirectionalLight[\n"
            "]");
    }
};

} // namespace lightwave

REGISTER_LIGHT(DirectionalLight, "directional")
