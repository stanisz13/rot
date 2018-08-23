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

struct DrawingEssentials
{
    unsigned program, VAO;
    unsigned modelLoc, texLoc, positionOfTexLoc, spritesPerDimensionsLoc;
};

struct TextureData
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

struct BoundingBox
{
    glm::fvec2 position;
    glm::fvec2 size;
    glm::fvec2 posOffset;
};

struct Drawable
{
    glm::fmat4 model;
    glm::fvec2 scaler;
    glm::fvec2 position;

    TextureData* texData;
};

struct Moving
{
    glm::fvec2 velocity;
    float speed;
};

struct Sprite : Drawable, Moving
{
    glm::fvec2 dashingVector;
    float dashAffection;
    float dashingSpeed;
    bool isMoving;

    glm::fvec2 positionOfTex;
    glm::fvec2 spritesPerDimensions;
    float timeForOneAnimationFrame;
    float animationTime;
    glm::fvec2 movementLastFrame;

    BoundingBox box;
};

struct Particle : Drawable, Moving
{

};

struct StaticObject : Drawable
{
    BoundingBox box;
};

bool initDrawingEssentials(DrawingEssentials& de,
WindowData& windowData);

void initRocks(StaticObject rocks[], const int rocksCount,
const WindowData& windowData);

void initPlayer(Sprite& player,
const WindowData& windowData);

void draw(const Sprite& s, const DrawingEssentials& de);

void draw(const StaticObject& o, const DrawingEssentials& de);

void draw(const Particle& p, const DrawingEssentials& de);

void handlePressedKeys(GLFWwindow* window, std::map<int, bool>& keysPressed,
Sprite& player);

void updatePlayer(const float dt, Sprite& player, const WindowData& windowData,
StaticObject rocks[], const int rocksCount);
