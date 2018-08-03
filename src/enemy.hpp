#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;
using namespace std;

struct Enemy : Entity
{
    Enemy() {}
    void init(const Vector2f& position, const Vector2f& dimensions,
         Texture* texture) override;
    void init(const Vector2f& position, const Vector2f& dimensions,
         Texture* texture, Color* colorOfObject) override;
    void init(const Vector2f& position, Texture* texture) override;

    Enemy(const Vector2f& position, Texture* texture);
    Enemy(const Vector2f& position, const Vector2f& dimensions, Texture* texture);
    Enemy(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
            Color* colorOfObject);
};
