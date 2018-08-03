#include "enemy.hpp"

inline void Enemy::init(const Vector2f& position, const Vector2f& dimensions, Texture* texture)
{
    Entity::init(position, dimensions, texture);
}

inline void Enemy::init(const Vector2f& position, Texture* texture)
{
    Entity::init(position, texture);
}

inline void Enemy::init(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
            Color* colorOfObject)
{
    Entity::init(position, dimensions, texture, colorOfObject);
}

inline Enemy::Enemy(const Vector2f& position, const Vector2f& dimensions, Texture* texture)
{
    init(position, dimensions, texture);
}

inline Enemy::Enemy(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
        Color* colorOfObject)
{
    init(position, dimensions, texture, colorOfObject);
}

inline Enemy::Enemy(const Vector2f& position, Texture* texture)
{
    init(position, texture);
}
