#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;
using namespace std;

struct Hero : Entity
{
    Hero() {}
    virtual ~Hero() {}
    void init(const Vector2f& position, const Vector2f& dimensions, Texture* texture) override;
    void init(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
                Color* colorOfObject) override;
    Hero(const Vector2f& position, const Vector2f& dimensions, Texture* texture);
    Hero(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
            Color* colorOfObject);
};
