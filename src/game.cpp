#include "game.hpp"

using namespace sf;
using namespace std;

namespace Game
{
    void init(RenderWindow* windowPass)
    {
        window = windowPass;
        windowDim = {2000, 1300};
        setUpCameraAndWindow(window, windowDim);
        boi.init("assets/boi.png");
    }

    void update(const float& dt)
    {

    }

    void draw()
    {
        boi.drawSprite(window);
    }

    void deInit()
    {

    }
}
