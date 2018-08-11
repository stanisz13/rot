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

struct AnimatedEntity
{
    Entity* e;
    IntRect rect;
    Vector2i dimensionsOfFrame;
    float time;
    float frameTime = 0.3f;
    vector<int> directions = {3, 2, 0, 1}; //going: up, right, down, left
    int numberOfFrames = 4;
    int walkingIndexInDirections = 2;
};

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
    AnimatedEntity animHero;


    void init();
    void update(const float& dt);
    void draw();
    void deInit();
};
