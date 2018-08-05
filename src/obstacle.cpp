#include "obstacle.hpp"

inline void Obstacle::init(const Vector2f& position, const Vector2f& dimensions, Texture* texture)
{
    Entity::init(position, dimensions, texture);
}

inline void Obstacle::init(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
            const Color& colorOfObject)
{
    Entity::init(position, dimensions, texture, colorOfObject);
}

inline void Obstacle::init(const Vector2f& position, Texture* texture)
{
    Entity::init(position, texture);
}

inline Obstacle::Obstacle(const Vector2f& position, const Vector2f& dimensions, Texture* texture)
{
    init(position, dimensions, texture);
}

inline Obstacle::Obstacle(const Vector2f& position, const Vector2f& dimensions, Texture* texture,
        const Color& colorOfObject)
{
    init(position, dimensions, texture, colorOfObject);
}

inline Obstacle::Obstacle(const Vector2f& position, Texture* texture)
{
    init(position, texture);
}
