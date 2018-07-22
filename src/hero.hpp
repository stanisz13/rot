#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;
using namespace std;

struct Hero : Entity
{
    Hero() {}

    Hero(const char* path) : Entity(path) {}

};
