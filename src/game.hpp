#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
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
    unordered_map<Keyboard::Key, bool> keysPressed;

    void init();
    void update(const float& dt);
    void draw();
    void deInit();
};
