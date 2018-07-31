#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct DrawableBasis
{
    Vector2f pos;
    Vector2f size;
    Vector2f scaling;
    Texture* tex;
    Color* color;

    DrawableBasis() {};
    void init(const Vector2f& position, const Vector2f& dimensions, Texture* texture);
    void init(const Vector2f& position, const Vector2f& dimensions, Color* colorOfObject);
    DrawableBasis(const Vector2f& position, const Vector2f& dimensions, Texture* texture);
    DrawableBasis(const Vector2f& position, const Vector2f& dimensions, Color* colorOfObject);
};
