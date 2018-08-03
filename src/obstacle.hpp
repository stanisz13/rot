#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;
using namespace std;

struct Obstacle : Entity
{
    Obstacle() {}
    virtual ~Obstacle() {}
    void init(const Vector2f& position, const Vector2f& dimensions, Texture* texture) override;
    void init(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
                Color& colorOfObject) override;
    void init(const Vector2f& position, Texture* texture) override;

    Obstacle(const Vector2f& position, Texture* texture);
    Obstacle(const Vector2f& position, const Vector2f& dimensions, Texture* texture);
    Obstacle(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
            Color& colorOfObject);
};
