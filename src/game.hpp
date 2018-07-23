#pragma once
#include <SFML/Graphics.hpp>
#include "hero.hpp"
#include "entity.hpp"

using namespace std;
using namespace sf;

struct Game
{
    RenderWindow window;
    Vector2u windowDim;
    Clock clock;
    Hero boi;
//-------------------------------------
    void setUpCameraAndWindow();
    
    void init();
    void update(const float& dt);
    void draw();
    void deInit();
};
