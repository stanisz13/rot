#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct Quad
{
    const Vector2f& pos;
    const Vector2f& size;
    const Color& color;

    Quad() {};
    Quad(const Vector2f& position, const Vector2f& dimensions,
         const Color& colorOfBox);
    void draw(RenderWindow& window);
};
