#include <lightwave.hpp>

namespace lightwave {

class ImageTexture : public Texture {
    enum class BorderMode {
        Clamp,
        Repeat,
    };

    enum class FilterMode {
        Nearest,
        Bilinear,
    };

    ref<Image> m_image;
    float m_exposure;
    BorderMode m_border;
    FilterMode m_filter;

public:
    ImageTexture(const Properties &properties) {
        if (properties.has("filename")) {
            m_image = std::make_shared<Image>(properties);
        } else {
            m_image = properties.getChild<Image>();
        }
        m_exposure = properties.get<float>("exposure", 1);

        // clang-format off
        m_border = properties.getEnum<BorderMode>("border", BorderMode::Repeat, {
            { "clamp", BorderMode::Clamp },
            { "repeat", BorderMode::Repeat },
        });

        m_filter = properties.getEnum<FilterMode>("filter", FilterMode::Bilinear, {
            { "nearest", FilterMode::Nearest },
            { "bilinear", FilterMode::Bilinear },
        });
        // clang-format on
    }

    Color evaluate(const Point2 &uv) const override {
        float tx; // x of the texel
        float ty; // y of the texel
        float fracx;
        float fracy;
        switch (m_border) {
        case BorderMode::Clamp: {
            // get the floating point part of the number,
            // add 1 if negative, if positive just keep going
            float fracx = uv.x() - floor(uv.x());
            float fracy = ceil(uv.y()) - uv.y(); // this was the problem
            // dont forget that the y-axis is reversed since the origin is
            // top left, not bot left
            // look at how its defined in the assignment for the uv stuff
            tx = (int) fmin(m_image->resolution().x() * fracx,
                            m_image->resolution().x() - 1);
            ty = (int) fmin(m_image->resolution().y() * fracy,
                            m_image->resolution().y() - 1);
        }

        case BorderMode::Repeat: {
            // get the floating point part of the number,
            // add 1 if negative, if positive just keep going
            float fracx = uv.x() - floor(uv.x());
            float fracy = ceil(uv.y()) - uv.y(); // this was the problem
            // dont forget that the y-axis is reversed since the origin is
            // top left, not bot left
            // look at how its defined in the assignment for the uv stuff
            tx = m_image->resolution().x() * fracx;
            ty = m_image->resolution().y() * fracy;

            // res x is width, y is height. at least I hope so
        }
        }
        Color textured;
        switch (m_filter) {
        case FilterMode::Bilinear: {
            // first in x, then in y
            Color c00 = Color(m_image->get(Point2i(tx, ty)));
            Color c10 = Color(m_image->get(Point2i(tx + 1, ty)));
            Color c01 = Color(m_image->get(Point2i(tx, ty + 1)));
            Color c11 = Color(m_image->get(Point2i(tx + 1, ty + 1)));
            textured  = ((1 - fracx) * (1 - fracy) * c00) +
                       ((fracx) * (1 - fracy) * c10) +
                       ((1 - fracx) * (fracy) *c01) + ((fracx) * (fracy) *c11);
        }

        case FilterMode::Nearest: {
            textured = Color(m_image->get(Point2i(tx, ty)));
            // this is enough, just goes to the nearest texel to the point?
        }
        }
        return textured;
    }

    std::string toString() const override {
        return tfm::format(
            "ImageTexture[\n"
            "  image = %s,\n"
            "  exposure = %f,\n"
            "]",
            indent(m_image),
            m_exposure);
    }
};

} // namespace lightwave

REGISTER_TEXTURE(ImageTexture, "image")
