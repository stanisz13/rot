#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "obstacle.hpp"
#include <vector>

using namespace sf;
using namespace std;

struct Floor : DrawableSprite
{
    const unsigned obstaclesNumber = 6;
    vector<Obstacle*> obstacles;

    void generate(const Vector2u& floorSize);
    Floor() {};
};
