#include <lightwave.hpp>

namespace lightwave {

class PointLight final : public Light {
    const Point query_point;
    const Color power;
public:
    PointLight(const Properties &properties) : Light(properties) {
        Point query_point = (properties.get<Point>("position"));
        Color power = properties.get<Color>("power");
    }

    DirectLightSample sampleDirect(const Point &origin,
                                   Sampler &rng) const override {
        //NOT_IMPLEMENTED
        Vector wi = Vector(origin - query_point);
        float distance = wi.length();
        float surface_area = Pi4 * distance * distance;
        Color intensity = power / surface_area;
        Color weight = intensity;

        return DirectLightSample{wi.normalized(), weight, distance};
    }

    bool canBeIntersected() const override { return false; }

    std::string toString() const override {
        return tfm::format(
            "PointLight[\n"
            "]");
    }
};

} // namespace lightwave

REGISTER_LIGHT(PointLight, "point")
