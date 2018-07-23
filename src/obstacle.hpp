#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;
using namespace std;

struct Obstacle : Entity
{
    float speed;

    Obstacle() {}
    Obstacle(const char* path) : Entity(path) {}
};
