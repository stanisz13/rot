#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "hero.hpp"
#include "entity.hpp"
#include "enemy.hpp"
#include "obstacle.cpp"

using namespace std;
using namespace sf;

struct Game
{
    RenderWindow window;
    Vector2u windowDim;
    Clock clock;
    Hero boi;
    unordered_map<Keyboard::Key, bool> keysPressed;
    vector<Enemy*> enemies;
    vector<Obstacle*> obstacles;
    
    void init();
    void update(const float& dt);
    void draw();
    void deInit();
};
