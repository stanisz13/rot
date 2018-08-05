#include "game.hpp"

using namespace sf;
using namespace std;

inline float vecLen(const Vector2f& v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

inline void normalize(Vector2f& v)
{
    float len = vecLen(v);
    if (len)
        v /= vecLen(v);
}

inline void setUpCameraAndWindow(Game* game)
{
    game->window.create(VideoMode(game->windowDim.x, game->windowDim.y), "Rot.");
    game->window.setFramerateLimit(60);
    View camera({0, 0}, {(float)game->windowDim.x, (float)game->windowDim.y});
    game->window.setView(camera);
}

inline void handleOneKey(Game* game, const Keyboard::Key& key)
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

inline void handleKeyboardInput(Game* game)
{
    handleOneKey(game, Keyboard::Escape);
    handleOneKey(game, Keyboard::W);
    handleOneKey(game, Keyboard::S);
    handleOneKey(game, Keyboard::A);
    handleOneKey(game, Keyboard::D);
}

inline void checkIfWindowClosed(Game* game)
{
    if (game->keysPressed[Keyboard::Escape])
    {
        game->window.close();
    }
}

inline void handleHeroMovement(Game* game, Hero* hero, const vector<Obstacle*>& obstacles, const float& dt)
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

                if (movement.x != 0 && movement.y != 0)
                {
                    Vector2f beforeSlide = hero->pos;
                    float avgFriction =
                        (hero->friction + obstacles[i]->friction)/2;

                    hero->move({movement.x * avgFriction, 0});
                    if (hero->collidesWith(*obstacles[i]))
                    {
                        hero->move(beforeSlide - hero->pos);
                    }

                    Vector2f afterXTry = hero->pos;

                    hero->move({0, movement.y * avgFriction});
                    if (hero->collidesWith(*obstacles[i]))
                    {
                        hero->move(afterXTry - hero->pos);
                    }

                    for (unsigned j = 0; j<obstacles.size(); ++j)
                    {
                        if (i != j && hero->collidesWith(*obstacles[j]))
                        {
                            hero->move(beforeSlide - hero->pos);
                            break;
                        }
                    }
                }
            }
        }
    }
}

inline void loadTexture(Game* game, const string& name)
{
    Texture* tmp = new Texture;
    tmp->loadFromFile("assets/" + name + ".png");
    game->textures[name] = tmp;
}

inline void loadTextures(Game* game)
{
    loadTexture(game, "boi");
    loadTexture(game, "brock");
    loadTexture(game, "moss");
    loadTexture(game, "anim");
}

void Game::init()
{
    setUpCameraAndWindow(this);
    loadTextures(this);

    Texture* boiTex = textures["anim"];
    boi.init({0, 0}, {(float)boiTex->getSize().x / 4, (float)boiTex->getSize().y / 4}, boiTex);
    boi.speed = 600.0f;
    boi.scale({3, 3});
    IntRect rect(0, 0, boi.size.x/boi.scaling.x, boi.size.y/boi.scaling.y);
    boi.sprite.setTextureRect(rect);

    gameFloor.generate(textures, {windowDim.x, windowDim.y});
}

void Game::update(const float& dt)
{
    handleKeyboardInput(this);
    checkIfWindowClosed(this);
    handleHeroMovement(this, &boi, gameFloor.obstacles, dt);
}

void Game::draw()
{
    for (unsigned i = 0; i<gameFloor.mosses.size(); ++i)
    {
        window.draw(gameFloor.mosses[i]->box);
    }
    for (unsigned i = 0; i<gameFloor.obstacles.size(); ++i)
    {
        window.draw(gameFloor.obstacles[i]->sprite);
    }

    for (unsigned i = 0; i<enemies.size(); ++i)
    {
        window.draw(enemies[i]->sprite);
    }

    window.draw(boi.sprite);
}

void Game::deInit()
{
    for (unsigned i = 0; i < enemies.size(); ++i)
        delete enemies[i];

    for (unsigned i = 0; i < gameFloor.obstacles.size(); ++i)
        delete gameFloor.obstacles[i];

    for (unsigned i = 0; i < gameFloor.mosses.size(); ++i)
        delete gameFloor.mosses[i];

    for (auto&& e : textures)
        delete e.second;
}
