#pragma once
#include <SFML/Graphics.hpp>
#include "drawableBasis.hpp"

using namespace sf;
using namespace std;

struct Entity : DrawableBasis
{
    float friction = 0.7f;

    virtual void init(const char* path);
    virtual void move(const Vector2f& v);
    virtual void scale(const Vector2f& v);
    virtual bool collidesWith(const Entity& two);

    Entity() {};
    Entity(const char* path);
    virtual ~Entity() {}
};
