#include <lightwave.hpp>

namespace lightwave {

class Pathtracer : public SamplingIntegrator {

public:
    Pathtracer(const Properties &properties)
        : SamplingIntegrator(properties){ 
            
        NOT_IMPLEMENTED

    }

    Color Li(const Ray &ray, Sampler &rng) override{ 
        NOT_IMPLEMENTED 
        
    }

    std::string toString() const override {
        return tfm::format(
            "Pathtracer[\n"
            "  sampler = %s,\n"
            "  image = %s,\n"
            "]",
            indent(m_sampler),
            indent(m_image));
    }
};

} // namespace lightwave

REGISTER_INTEGRATOR(Pathtracer, "pathtracer")
