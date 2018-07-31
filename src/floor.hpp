#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "obstacle.hpp"
#include "quad.hpp"
#include <vector>

using namespace sf;
using namespace std;

struct Floor : DrawableSprite
{
    const unsigned obstaclesNumber = 6;
    vector<Obstacle*> obstacles;
    const unsigned mossesNumber = obstaclesNumber;
    vector<Quad*> mosses;

    void generate(const Vector2u& floorSize);
    Floor() {};
};
