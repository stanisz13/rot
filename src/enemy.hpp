#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;
using namespace std;

struct Enemy : Entity
{
    float speed;

    Enemy() {}
    Enemy(const char* path) : Entity(path) {}
};
