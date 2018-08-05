#include "entity.hpp"
#include <iostream>

inline void Entity::init(const Vector2f& position, const Vector2f& dimensions, Texture* texture)
{
    DrawableBasis::init(position, dimensions, texture);
    sprite.setTexture(*tex);
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(pos.x, pos.y);
}

inline void Entity::init(const Vector2f& position, Texture* texture)
{
    DrawableBasis::init(position, texture);
    sprite.setTexture(*tex);
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(pos.x, pos.y);
}

inline void Entity::init(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
                    const Color& colorOfObject)
{
    DrawableBasis::init(position, dimensions, texture);
    sprite.setTexture(*tex);
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(pos.x, pos.y);
    sprite.setColor(colorOfObject);
}


inline Entity::Entity(const Vector2f& position, const Vector2f& dimensions, Texture* texture)
{
    init(position, dimensions, texture);
}
inline Entity::Entity(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
                const Color& colorOfObject)
{
    init(position, dimensions, texture, colorOfObject);
}

inline Entity::Entity(const Vector2f& position, Texture* texture)
{
    init(position, texture);
}

void Entity::move(const Vector2f& v)
{
    pos += v;
    sprite.setPosition(pos);
}

void Entity::scale(const Vector2f& v)
{
    scaling.x *= v.x;
    scaling.y *= v.y;
    size.x *= v.x;
    size.y *= v.y;
    sprite.setScale(scaling.x, scaling.y);
}

bool Entity::collidesWith(const Entity& two)
{
    Vector2f oneTexSize = (Vector2f)size;
    Vector2f twoTexSize = (Vector2f)two.size;

    Vector2f p1 = {pos.x - oneTexSize.x/2, pos.y - oneTexSize.y/2};
    Vector2f p2 = {two.pos.x - twoTexSize.x/2, two.pos.y - twoTexSize.y/2};


    bool collidesX = p1.x + oneTexSize.x >= p2.x &&
        p2.x + twoTexSize.x >= p1.x;

    bool collidesY = p1.y + oneTexSize.y >= p2.y &&
        p2.y + twoTexSize.y >= p1.y;

    return collidesX && collidesY;
}
