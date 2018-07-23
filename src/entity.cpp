#include "entity.hpp"
#include <iostream>

void Entity::init(const char* path)
{
    loadTexture(path);
    sprite.setTexture(tex);
    texSize = tex.getSize();
    sprite.setOrigin(texSize.x/2, texSize.y/2);
    sprite.setColor(Color(255, 255, 255, 255));
    sprite.setPosition(0, 0);
    pos = {0, 0};
}

Entity::Entity(const char* path)
{
    init(path);
}
    
void Entity::drawSprite(RenderWindow& window)
{
    window.draw(sprite);
}

void Entity::loadTexture(const char* path)
{
    tex.loadFromFile(path);
}

void Entity::move(const Vector2f& v)
{
    pos += v;
    sprite.setPosition(pos);
}

bool Entity::collidesWith(const Entity& two)
{
    Vector2f oneTexSize = (Vector2f)tex.getSize();
    Vector2f twoTexSize = (Vector2f)two.tex.getSize();

    Vector2f p1 = {pos.x - oneTexSize.x/2, pos.y - oneTexSize.y/2};
    Vector2f p2 = {two.pos.x - twoTexSize.x/2, two.pos.y - twoTexSize.y/2};

    
    bool collidesX = p1.x + oneTexSize.x >= p2.x &&
        p2.x + twoTexSize.x >= p1.x;

    bool collidesY = p1.y + oneTexSize.y >= p2.y &&
        p2.y + twoTexSize.y >= p1.y;

    return collidesX && collidesY;
}

