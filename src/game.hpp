#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <string>

#include "hero.hpp"
#include "entity.hpp"
#include "enemy.hpp"
#include "obstacle.cpp"
#include "floor.hpp"

using namespace std;
using namespace sf;

struct Game
{
    RenderWindow window;
    Vector2u windowDim = {1600, 900};
    Clock clock;
    Hero boi;
    unordered_map<Keyboard::Key, bool> keysPressed;
    vector<Enemy*> enemies;
    Floor gameFloor;
    unordered_map<string, Texture*> textures;


    void init();
    void update(const float& dt);
    void draw();
    void deInit();
};
