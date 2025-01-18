#include <lightwave.hpp>

namespace lightwave {

class Thinlens : public Camera {

    float scale_x;
    float scale_y;
    float radius;
    float focal_dis;

public:
    Thinlens(const Properties &properties) : Camera(properties) {

        radius    = properties.get<float>("radius");
        focal_dis = properties.get<float>("focalDistance");

        // const float fov =  ;
    }

    CameraSample sample(const Point2 &normalized, Sampler &rng) const override {

    }

    std::string toString() const override {
        return tfm::format(
            "Thinlens[\n]"
            " width = %d,\n"
            " height = %d,\n"
            " trransform = %s,\n"
            "]",
            m_resolution.x(),
            m_resolution.y(),
            indent(m_transform));
    }
};

} // namespace lightwave

REGISTER_CAMERA(Thinlens, "thinlens")
