#include "quad.hpp"

inline void Quad::init(const Vector2f& position, const Vector2f& dimensions,
     Color* colorOfBox)
{
    DrawableBasis::init(position, dimensions, colorOfBox);

    box.setSize(size);
    box.setFillColor(*color);
    box.setOrigin(size.x/2, size.y/2);
    box.setPosition(pos);
}

inline void Quad::init(const Vector2f& position, const Vector2f& dimensions,
     Texture* texture)
{
    DrawableBasis::init(position, dimensions, texture);

    box.setSize(size);
    box.setOrigin(size.x/2, size.y/2);
    box.setPosition(pos);
    box.setTexture(tex, 0);
}

inline void Quad::init(const Vector2f& position, Texture* texture)
{
    DrawableBasis::init(position, texture);

    box.setSize(size);
    box.setOrigin(size.x/2, size.y/2);
    box.setPosition(pos);
    box.setTexture(tex, 0);
}

inline Quad::Quad(const Vector2f& position, const Vector2f& dimensions,
     Color* colorOfBox)
{
    init(position, dimensions, colorOfBox);
}
Quad::Quad(const Vector2f& position, const Vector2f& dimensions,
     Texture* texture)
{
    init(position, dimensions, texture);
}

inline void Quad::move(const Vector2f& v)
{
    pos += v;
    box.setPosition(pos);
}

inline void Quad::scale(const Vector2f& v)
{
    scaling.x *= v.x;
    scaling.y *= v.y;
    size.x *= v.x;
    size.y *= v.y;
    box.setScale(scaling.x, scaling.y);
}
