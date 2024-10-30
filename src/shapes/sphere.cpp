#include <lightwave.hpp>

namespace lightwave {
class Sphere : public Shape { 
    public:
        Sphere(const Properties &properties) { 
            NOT_IMPLEMENTED
        }
        bool intersect(const Ray &ray, Intersection &its, Sampler &rng) const override {
            //NOT_IMPLEMENTED
            PROFILE("SPHERE")

        }
        Bounds getBoundingBox() const override { 
            //NOT_IMPLEMENTED
            return Bounds(Point{ -1, -1, -1}, Point{ +1, +1, +1});
        }
        Point getCentroid() const override {
            //NOT_IMPLEMENTED
            return Point(0);
        }
        AreaSample sampleArea(Sampler &rng) const override {
            NOT_IMPLEMENTED // leave it for 1.2.2
        }
        std::string toString() const override { 
            return "Sphere[]";
        } 
};
}
REGISTER_SHAPE(Sphere, "sphere")
