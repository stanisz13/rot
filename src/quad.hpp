#pragma once
#include <SFML/Graphics.hpp>
#include "drawableBasis.hpp"

using namespace sf;
using namespace std;

struct Quad : DrawableBasis
{
    RectangleShape box;

    Quad() {};
    virtual ~Quad() {}
    void init(const Vector2f& position, const Vector2f& dimensions,
         Color* colorOfBox) override;
    void init(const Vector2f& position, const Vector2f& dimensions,
         Texture* texture);
    Quad(const Vector2f& position, const Vector2f& dimensions,
         Color* colorOfBox);
    Quad(const Vector2f& position, const Vector2f& dimensions,
         Texture* texture);

    void draw(RenderWindow& window);
    void move(const Vector2f& v);
    void scale(const Vector2f& v);
};
