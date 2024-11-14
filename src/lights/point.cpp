#include <lightwave.hpp>

namespace lightwave {

class PointLight final : public Light {
    Point query_point;
    Color power;

public:
    PointLight(const Properties &properties) : Light(properties) {
        query_point = (properties.get<Point>("position"));
        power       = properties.get<Color>("power");
    }

    DirectLightSample sampleDirect(const Point &origin,
                                   Sampler &rng) const override {
        // NOT_IMPLEMENTED
        Vector wi          = Vector(query_point - origin);
        float surface_area = Pi * 4 * wi.dot(wi);
        Color intensity    = power / surface_area;
        Color weight       = intensity;

        return DirectLightSample{ wi.normalized(), weight, wi.length() };
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
