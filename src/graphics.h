#pragma once
/* ========================================================================
   $File: graphics.cpp $
   $Date: 18.04.18 $
   $Creator: Stanisz $
   ======================================================================== */
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"
#include "stb/stb.h"

struct WindowData
{
    int width = 900;
    int height = 600;
    float aspectRatio = (float)width/height;
    int contextVersionMajor = 3;
    int contextVersionMinor = 3;
    GLFWwindow* pointer;
    const char* name = "2D!";
};

struct drawingEssentials
{
    unsigned program, VAO;
    unsigned modelLoc, texLoc, positionOfTexLoc, spritesPerDimensionsLoc;
};

struct textureData
{
    std::string path;

    unsigned texture;

    float width;
    float height;
    float aspectRatio;

    int numberOfChannels;

    int spritesInOneRow;
    int spritesInOneCollumn;
};

struct boundingBox
{
    glm::fvec2 position;
    glm::fvec2 size;
};

struct drawable
{
    glm::fmat4 model;
    glm::fvec2 scaler;
    glm::fvec2 position;
};

struct moving
{
    glm::fvec2 velocity;
    float speed;
};

struct sprite : drawable, moving
{
    textureData* texData;

    glm::fvec2 dashingVector;
    float dashAffection;
    float dashingSpeed;
    bool isMoving;

    glm::fvec2 positionOfTex;
    glm::fvec2 spritesPerDimensions;
    float timeForOneAnimationFrame;
    float animationTime;
    glm::fvec2 movementLastFrame;

    boundingBox box;
};

struct particle : drawable, moving
{

};

struct staticObject : drawable
{
    textureData* texData;
    boundingBox box;
};

bool initDrawingEssentials(drawingEssentials& de,
WindowData& windowData);

void initParticles(particle particles[], const int particlesCount,
std::map<std::string, textureData*>& textureDatas,
const WindowData& windowData);

void initRocks(staticObject rocks[], const int rocksCount,
std::map<std::string, textureData*>& textureDatas,
const WindowData& windowData);

void initPlayer(sprite& player,
const WindowData& windowData);

void draw(const sprite& s, const drawingEssentials& de);

void draw(const staticObject& o, const drawingEssentials& de);

void draw(const particle& p, const drawingEssentials& de);

void handlePressedKeys(GLFWwindow* window, std::map<int, bool>& keysPressed,
sprite& player);

void updatePlayer(const float dt, sprite& player, const WindowData& windowData,
staticObject rocks[], const int rocksCount);
