#pragma once
#include <SFML/Graphics.hpp>
#include "hero.hpp"
#include "entity.hpp"

using namespace std;
using namespace sf;

namespace Game
{
    RenderWindow* window;
    Vector2u windowDim;
    
    Clock clock;

    Hero boi;

    void init(sf::RenderWindow* windowPass);
    void update(const float& dt);
    void draw();
    void deInit();
}
