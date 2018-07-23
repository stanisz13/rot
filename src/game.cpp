#include "game.hpp"

using namespace sf;
using namespace std;

void Game::setUpCameraAndWindow()
{
    window.create(VideoMode(windowDim.x, windowDim.y), "Rot.");
    window.setFramerateLimit(60);
    View camera({0, 0}, {(float)windowDim.x, (float)windowDim.y});
    window.setView(camera);
}
    
void Game::init()
{
    windowDim = {2000, 1300};
    setUpCameraAndWindow();
    boi.init("assets/boi.png");
}

void Game::update(const float& dt)
{

}

void Game::draw()
{
    boi.drawSprite(window);
}

void Game::deInit()
{

}

