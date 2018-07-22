#include "entity.hpp"


struct Entity
{
    void init(const char* path)
    {
        loadTexture(path);
        sprite.setTexture(tex);
        texSize = tex.getSize();
        sprite.setOrigin(texSize.x/2, texSize.y/2);
        sprite.setPosition(0, 0);
    }

    Entity(const char* path)
    {
        init(path);
    }
    
    void drawSprite(RenderWindow& window)
    {
        window.draw(sprite);
    }

    void loadTexture(const char* path)
    {
        tex.loadFromFile(path);
    }
};
