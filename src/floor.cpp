#include "floor.hpp"
#include <iostream>


using namespace sf;
using namespace std;

void Floor::generate(unordered_map<string, Texture*>& textures, const Vector2u& floorSize)
{
    Texture* brockTex = textures["brock"];
    Texture* mossTex = textures["moss"];

    for (unsigned i=0; i<obstaclesNumber; ++i)
    {
        Obstacle* now = new Obstacle;
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

        now->init({(float)xRand, (float)yRand}, brockTex);
        now->scale({0.3, 0.3});
        obstacles.emplace_back(now);
    }

    for (unsigned i=0; i<mossesNumber; ++i)
    {
        Obstacle& rock = *obstacles[i];

        Quad* now = new Quad(rock.pos,
                            {(float)rock.size.x + mossesAddedSize,
                                (float)rock.size.y + mossesAddedSize},
                            mossTex);

        mosses.emplace_back(now);
    }


}
