#include <lightwave.hpp>

namespace lightwave {

class DirectionalLight final : public Light {
    const Vector direction;
    const Color power;
public:
    DirectionalLight(const Properties &properties) : Light(properties) {
        Vector direction = properties.get<Vector>("direction");
        Color power = properties.get<Color>("power");
    }

    DirectLightSample sampleDirect(const Point &origin,
                                   Sampler &rng) const override {
        Vector wi = -direction;
        Color weight = power;
        return DirectLightSample{direction.normalized(), weight, Infinity};
    }

    bool canBeIntersected() const override { return false; }

    std::string toString() const override {
        return tfm::format(
            "DirectionalLight[\n"
            "]");
    }
};

} // namespace lightwave

REGISTER_LIGHT(DirectionalLight, "point")
