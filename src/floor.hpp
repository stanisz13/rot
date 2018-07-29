#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

using namespace sf;
using namespace std;

struct Floor : DrawableSprite
{
    void generate();
    Floor() {};
};
