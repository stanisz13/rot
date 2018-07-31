#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct Quad
{
    RectangleShape box;

    Vector2f pos;
    Vector2f size;
    Color color;

    Texture tex;

    Quad() {};
    void init(const Vector2f& position, const Vector2f& dimensions,
         const Color& colorOfBox);
    void init(const Vector2f& position, const Vector2f& dimensions,
         const Texture& texture);
    Quad(const Vector2f& position, const Vector2f& dimensions,
         const Color& colorOfBox);
    Quad(const Vector2f& position, const Vector2f& dimensions,
         const Texture& texture);
    void draw(RenderWindow& window);
    void move(const Vector2f& v);
    void scale(const Vector2f& v);
};
