#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;
using namespace std;

struct Hero : Entity
{
    float speed;

    Hero() {}
    Hero(const char* path) : Entity(path) {}
};
