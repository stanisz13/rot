#include "quad.hpp"

void Quad::init(const Vector2f& position, const Vector2f& dimensions,
        const Color& colorOfBox)
{
    pos = position;
    size = dimensions;
    color = colorOfBox;

    box.setSize(size);
    box.setFillColor(color);
    box.setOrigin(size.x/2, size.y/2);
    box.setPosition(pos);
}
Quad::Quad(const Vector2f& position, const Vector2f& dimensions,
        const Color& colorOfBox)
{
    init(position, dimensions, colorOfBox);
}
void Quad::init(const Vector2f& position, const Vector2f& dimensions,
     const Texture& texture)
{
    pos = position;
    size = dimensions;
    tex = texture;

    box.setSize(size);
    box.setOrigin(size.x/2, size.y/2);
    box.setPosition(pos);
    box.setTexture(&tex, 0);
}

Quad::Quad(const Vector2f& position, const Vector2f& dimensions,
     const Texture& texture)
{
    init(position, dimensions, texture);
}

void Quad::draw(RenderWindow& window)
{
    window.draw(box);
}

void Quad::move(const Vector2f& v)
{
    pos += v;
    box.setPosition(pos);
}

void Quad::scale(const Vector2f& v)
{
    box.setScale(box.getScale().x * v.x, box.getScale().y * v.y);
}
