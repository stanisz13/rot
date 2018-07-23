#include "game.hpp"
#include <cmath>

using namespace sf;
using namespace std;

float vecLen(const Vector2f& v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

void normalize(Vector2f& v)
{
    float len = vecLen(v);
    if (len)
        v /= vecLen(v);
}

void setUpCameraAndWindow(Game* game)
{
    game->window.create(VideoMode(game->windowDim.x, game->windowDim.y), "Rot.");
    game->window.setFramerateLimit(60);
    View camera({0, 0}, {(float)game->windowDim.x, (float)game->windowDim.y});
    game->window.setView(camera);
}

void handleOneKey(Game* game, const Keyboard::Key& key)
{
    if (Keyboard::isKeyPressed(key))
    {
        game->keysPressed[key] = 1;
    }
    else
    {
        game->keysPressed[key] = 0;
    }
}

void handleKeyboardInput(Game* game)
{
    handleOneKey(game, Keyboard::Escape);
    handleOneKey(game, Keyboard::W);
    handleOneKey(game, Keyboard::S);
    handleOneKey(game, Keyboard::A);
    handleOneKey(game, Keyboard::D);
}

void checkIfWindowClosed(Game* game)
{
    if (game->keysPressed[Keyboard::Escape])
    {
        game->window.close();
    }
}

void displayCollisionBox(Game* game, const Entity& e)
{
    RectangleShape box;
    Vector2f texSize = (Vector2f)e.tex.getSize();
    box.setSize(texSize);
    box.setFillColor(Color(255, 0, 0, 200));
    box.setPosition(e.pos.x - texSize.x/2, e.pos.y - texSize.y/2);
    
    game->window.draw(box);
}

void handleHeroMovement(Game* game, Hero* hero, const vector<Obstacle*>& obstacles, const float& dt)
{
    Vector2f movement = {0, 0};
    
    if (game->keysPressed[Keyboard::W])
    {
        movement += Vector2f(0, -1);
    }

    if (game->keysPressed[Keyboard::S])
    {
        movement += Vector2f(0, 1);
    }

    if (game->keysPressed[Keyboard::A])
    {
        movement += Vector2f(-1, 0);
    }

    if (game->keysPressed[Keyboard::D])
    {
        movement += Vector2f(1, 0);
    }

    normalize(movement);

    if (movement != Vector2f(0, 0))
    {
        movement *= hero->speed;
        movement *= dt;

        Vector2f heroPosBeforeMovement = hero->pos;
        hero->move(movement);

        for (unsigned i = 0; i<obstacles.size(); ++i)
        {
            if (hero->collidesWith(*obstacles[i]))
            {
                Vector2f currentHeroPosition = hero->pos;
                hero->move(heroPosBeforeMovement - currentHeroPosition);
            }
        }    
    }
}
    
void Game::init()
{
    windowDim = {2000, 1300};
    setUpCameraAndWindow(this);

    boi.init("assets/boi.png");
    boi.speed = 600.0f;

    Obstacle* brock = new Obstacle("assets/brock.png");
    brock->move(Vector2f(500, 0));
    obstacles.emplace_back(brock);
}

void Game::update(const float& dt)
{    
    handleKeyboardInput(this);
    checkIfWindowClosed(this);
    handleHeroMovement(this, &boi, obstacles, dt);
}

void Game::draw()
{
    for (unsigned i = 0; i<enemies.size(); ++i)
    {
        enemies[i]->drawSprite(window);
    }

    for (unsigned i = 0; i<obstacles.size(); ++i)
    {
        obstacles[i]->drawSprite(window);
    }
    
    boi.drawSprite(window);

    displayCollisionBox(this, boi);
    displayCollisionBox(this, *obstacles[0]);
}

void Game::deInit()
{
    for (unsigned i = 0; i < enemies.size(); ++i)
        delete enemies[i];
    
    for (unsigned i = 0; i < obstacles.size(); ++i)
        delete obstacles[i];
}

