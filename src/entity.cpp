#include "entity.hpp"


void Entity::init(const char* path)
{
    loadTexture(path);
    sprite.setTexture(tex);
    texSize = tex.getSize();
    sprite.setOrigin(texSize.x/2, texSize.y/2);
    sprite.setPosition(0, 0);
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

