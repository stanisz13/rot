#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>

#include "utils.h"
#include "graphics.h"

DrawingEssentials basic;
WindowData windowData;
std::map<int, bool> keysPressed;
const int rocksCount = 5;
StaticObject rocks[rocksCount];
Sprite player;

inline bool initAll()
{
    if (!initDrawingEssentials(basic, windowData))
    {
        return 0;
    }
    srand(1337691);
    initPlayer(player, windowData);
    initRocks(rocks, rocksCount, windowData);

    return 1;
}

inline void deInitAll()
{
    delete player.texData;

    for (int i = 0; i<rocksCount; ++i)
    {
        delete rocks[i].texData;
    }
}

inline void updateAll(float dt)
{
    glfwPollEvents();
    handlePressedKeys(windowData.pointer, keysPressed, player);
    updatePlayer(dt, player, windowData, rocks, rocksCount);
}

inline void drawAll()
{
    glClearColor(0.2f, 1.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    //ROCKS-----------------------------------------
    for (auto&& r : rocks)
    {
        glBindTexture(GL_TEXTURE_2D, r.texData->texture);
        draw(r, basic);
    }
    //END OF ROCK -----------------------------------
    //PLAYER----------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, player.texData->texture);
    draw(player, basic);
    //END OF PLAYER-------------------------------------------
    glfwSwapBuffers(windowData.pointer);
}

int main()
{
    //LOADING--------------------------------------------------
    float beginningOfLoadTime = glfwGetTime();

    if (!initAll())
    {
        return 0;
    }

    float loadingTime = glfwGetTime() - beginningOfLoadTime;
    LOG(loadingTime);
    //END OF LOADING------------------------------------------------
    float dt = 0;
    float maxTimeToRenderOneFrame = 0;
    long long framesSinceTheBeginningOfGame = 0;

    while(!glfwWindowShouldClose(windowData.pointer))
    {
        float timeBeforeFrame = glfwGetTime();

        //UPDATE--------------------------------------------
        updateAll(dt);
        //END OF UPDATE---------------------------------------
        //DRAWING-------------------------------------------------------
        drawAll();

        framesSinceTheBeginningOfGame++;
        if (framesSinceTheBeginningOfGame > (long long)(1<<30))
        {
            framesSinceTheBeginningOfGame = 0;
            LOG("modulated framesSinceTheBeginningOfGame!");
        }

        if (framesSinceTheBeginningOfGame % 1000 == 0)
        {
            LOG(maxTimeToRenderOneFrame * 1000);
            maxTimeToRenderOneFrame = 0;
        }

        float timeAfterFrame = glfwGetTime();
        dt = timeAfterFrame - timeBeforeFrame;
        maxTimeToRenderOneFrame = fmax(maxTimeToRenderOneFrame, dt);

        if (player.isMoving)
            player.animationTime += dt;
    }

    deInitAll();

    return 0;
}
