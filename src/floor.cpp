#include "floor.hpp"
#include <iostream>


using namespace sf;
using namespace std;

void Floor::generate(const Vector2u& floorSize)
{
    for (unsigned i=0; i<obstaclesNumber; ++i)
    {
        Obstacle* now = new Obstacle;
        now->init("assets/brock.png");
        unsigned randOffset = 300;
        int xRand = rand()%(floorSize.x/2 - randOffset) + randOffset;
        int yRand = rand()%(floorSize.y/2 - randOffset) + randOffset;
        if (rand()%2)
        {
            xRand *= -1;
        }
        if (rand()%2)
        {
            yRand *= -1;
        }
        now->move({(float)xRand, (float)yRand});
        now->scale({0.3, 0.3});
        obstacles.emplace_back(now);
    }

    Texture mossTex;
    mossTex.loadFromFile("assets/moss.png");
    for (unsigned i=0; i<mossesNumber; ++i)
    {
        Obstacle& rock = *obstacles[i];

        Quad* now = new Quad(rock.pos,
                            {(float)rock.texSize.x + mossesAddedSize,
                                (float)rock.texSize.y + mossesAddedSize},
                            &mossTex);

        mosses.emplace_back(now);
    }


}
