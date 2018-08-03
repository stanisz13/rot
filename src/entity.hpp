#pragma once
#include <SFML/Graphics.hpp>
#include "drawableBasis.hpp"

using namespace sf;
using namespace std;

struct Entity : DrawableBasis
{
    Sprite sprite;
    float friction = 0.7f;
    float speed;

    void move(const Vector2f& v);
    void scale(const Vector2f& v);
    bool collidesWith(const Entity& two);

    Entity() {};
    virtual ~Entity() {}
    virtual void init(const Vector2f& position, const Vector2f& dimensions, Texture* texture) override;
    virtual void init(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
                Color& colorOfObject);
    virtual void init(const Vector2f& position, Texture* texture);

    Entity(const Vector2f& position, Texture* texture);
    Entity(const Vector2f& position, const Vector2f& dimensions, Texture* texture);
    Entity(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
                Color& colorOfObject);
};
