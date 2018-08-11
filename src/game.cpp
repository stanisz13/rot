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

inline void setAnimFrameToZero(AnimatedEntity& a)
{
    a.rect.left = 0;
    a.rect.top = a.directions[2] * a.dimensionsOfFrame.y;
    a.e->sprite.setTextureRect(a.rect);
}

inline void moveAnimOneFrameX(AnimatedEntity& a)
{
    if (a.rect.left + a.dimensionsOfFrame.x < a.dimensionsOfFrame.x * a.numberOfFrames)
    {
        a.rect.left += a.dimensionsOfFrame.x;
    }
    else
    {
        a.rect.left = 0;
    }

    a.e->sprite.setTextureRect(a.rect);
}

inline void startWalkingInDir(AnimatedEntity& a, int dir)
{
    a.rect.left = 0;
    a.rect.top = a.directions[dir] * a.dimensionsOfFrame.y;
    a.e->sprite.setTextureRect(a.rect);
}

inline void handleHeroMovement(Game* game, AnimatedEntity& ae, const vector<Obstacle*>& obstacles, const float& dt)
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
        movement *= ae.e->speed;
        movement *= dt;
        ae.time += dt;

        int walkingDirNow;

        if (movement.x > 0)
        {
            walkingDirNow = 1;
        }
        if (movement.x < 0)
        {
            walkingDirNow = 3;
        }
        if (movement.y < 0)
        {
            walkingDirNow = 0;
        }
        if (movement.y > 0)
        {
            walkingDirNow = 2;
        }

        if (ae.walkingIndexInDirections != walkingDirNow)
        {
            startWalkingInDir(ae, walkingDirNow);
            ae.time = 0.0f;
            ae.walkingIndexInDirections = walkingDirNow;
        }

        if (ae.time >= ae.frameTime)
        {
            moveAnimOneFrameX(ae);
            ae.time = 0.0f;
        }

        Vector2f heroPosBeforeMovement = ae.e->pos;
        ae.e->move(movement);

        for (unsigned i = 0; i<obstacles.size(); ++i)
        {
            if (ae.e->collidesWith(*obstacles[i]))
            {
                Vector2f currentHeroPosition = ae.e->pos;
                ae.e->move(heroPosBeforeMovement - currentHeroPosition);

                if (movement.x != 0 && movement.y != 0)
                {
                    Vector2f beforeSlide = ae.e->pos;
                    float avgFriction =
                        (ae.e->friction + obstacles[i]->friction)/2;

                    ae.e->move({movement.x * avgFriction, 0});
                    if (ae.e->collidesWith(*obstacles[i]))
                    {
                        ae.e->move(beforeSlide - ae.e->pos);
                    }

                    Vector2f afterXTry = ae.e->pos;

                    ae.e->move({0, movement.y * avgFriction});
                    if (ae.e->collidesWith(*obstacles[i]))
                    {
                        ae.e->move(afterXTry - ae.e->pos);
                    }

                    for (unsigned j = 0; j<obstacles.size(); ++j)
                    {
                        if (i != j && ae.e->collidesWith(*obstacles[j]))
                        {
                            ae.e->move(beforeSlide - ae.e->pos);
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

    animHero.e = &boi;
    animHero.dimensionsOfFrame = {(int)boiTex->getSize().x / 4, (int)boiTex->getSize().y / 4};
    animHero.rect = {{0, 0}, animHero.dimensionsOfFrame};

    boi.init({(float)animHero.rect.left, (float)animHero.rect.top},
      {(float)animHero.rect.width, (float)animHero.rect.height}, boiTex);
    boi.speed = 100.0f;
    boi.scale({3, 3});
    IntRect rect(0, 0, boi.size.x/boi.scaling.x, boi.size.y/boi.scaling.y);
    boi.sprite.setTextureRect(rect);

    gameFloor.generate(textures, {windowDim.x, windowDim.y});
}

void Game::update(const float& dt)
{
    handleKeyboardInput(this);
    checkIfWindowClosed(this);
    handleHeroMovement(this, animHero, gameFloor.obstacles, dt);
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
    window.close();

    for (unsigned i = 0; i < enemies.size(); ++i)
        delete enemies[i];

    for (unsigned i = 0; i < gameFloor.obstacles.size(); ++i)
        delete gameFloor.obstacles[i];

    for (unsigned i = 0; i < gameFloor.mosses.size(); ++i)
        delete gameFloor.mosses[i];

    for (auto&& e : textures)
        delete e.second;
}
