#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct Entity
{
    Texture tex;
    Sprite sprite;
    Vector2f pos;
    Vector2u texSize;


    void init(const char* path);

    Entity() {};
    Entity(const char* path);

    void drawSprite(RenderWindow& window);

    void loadTexture(const char* path);    
};
