#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct DrawableSprite
{
    Texture tex;
    Sprite sprite;
    Vector2f pos;
    Vector2u texSize;

    virtual void drawSprite(RenderWindow& window);
    virtual void loadTexture(const char* path);
    virtual ~DrawableSprite() {};
};

struct Entity : DrawableSprite
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
