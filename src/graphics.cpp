#include "graphics.h"

#define STANISZ_DEBUG

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    extern std::map<int, bool> keysPressed;
    if (action == GLFW_PRESS)
        keysPressed[key] = 1;
    if (action == GLFW_RELEASE)
        keysPressed[key] = 0;
}

void resize_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    extern WindowData windowData;

    windowData.width = newWidth;
    windowData.height = newHeight;
    glViewport(0, 0, newWidth, newHeight);
}

void loadTexture(TextureData* texData)
{
    glGenTextures(1, &texData->texture);
    glBindTexture(GL_TEXTURE_2D, texData->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int readWidth, readHeight;
    unsigned char *data = stbi_load(texData->path.c_str(), &readWidth, &readHeight, &texData->numberOfChannels, 0);
    texData->width = readWidth;
    texData->height = readHeight;

    texData->aspectRatio = (float)texData->width / texData->height;

    if (data)
    {
        if (texData->numberOfChannels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texData->width, texData->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texData->width, texData->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        LOG("Failed to load texture");
    }

    stbi_image_free(data);
}

void initSprite(Sprite& s, const char* pathToTexture, const float windowAspectRatio,
                const int spritesInOneRow, const int spritesInOneCollumn)
{
    s.texData->path = pathToTexture;
    loadTexture(s.texData);

    s.position = glm::fvec2(0, 0);

    s.texData->spritesInOneCollumn = spritesInOneCollumn;
    s.texData->spritesInOneRow = spritesInOneRow;

    s.spritesPerDimensions = {spritesInOneRow, spritesInOneCollumn};
}

void setUpBasicVAO(unsigned& VAO)
{
    GLfloat Vertices[] = {
        //vertices         //tex coords
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 3
    };

    unsigned EBO, VBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

const std::string LoadShaderCode(const char* Path)
{
    std::ifstream File(Path, std::ios::in);
    std::stringstream Stream;

    if (File.is_open() == 0)
    {
        LOG("Shader source code from path '" + (std::string)Path + "' failed!");
        return (0);
    }

    Stream << File.rdbuf();
    File.close();
    std::string Code = Stream.str();

    return (Code);
}

GLuint CreateShader(const char* Path, const int ShaderType)
{
    if (ShaderType > 2)
    {
        LOG("Invalid argument in CreateShader function,'ShaderType' should be 0, 1 or 2.");

        return (0);
    }

    if (ShaderType == 0)
    {
        GLuint Shader = glCreateShader(GL_VERTEX_SHADER);

        const std::string &&ShaderSource = LoadShaderCode(Path);

        const char* Cstring = ShaderSource.c_str();

        glShaderSource(Shader, 1, &Cstring, NULL);
        glCompileShader(Shader);

#ifdef STANISZ_DEBUG
        int CompilationStatus;
        char InfoLOG[512];
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompilationStatus);

        if (CompilationStatus == GL_FALSE)
        {
            glGetShaderInfoLog(Shader, 512, NULL, InfoLOG);

            LOG("Vertex shader from path '" + (std::string)Path
                + "' compilation failed!\n" + (std::string)InfoLOG);
        }
#endif

        return (Shader);
    }

    if (ShaderType == 1)
    {
        GLuint Shader = glCreateShader(GL_FRAGMENT_SHADER);

        const std::string &&ShaderSource = LoadShaderCode(Path);
        const char* Cstring = ShaderSource.c_str();

        glShaderSource(Shader, 1, &Cstring, NULL);
        glCompileShader(Shader);

#ifdef STANISZ_DEBUG
        int CompilationStatus;
        char InfoLOG[512];
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompilationStatus);

        if (CompilationStatus == GL_FALSE)
        {
            glGetShaderInfoLog(Shader, 512, NULL, InfoLOG);

            LOG("Fragment shader from path '" + (std::string)Path
                + "' compilation failed!\n" + (std::string)InfoLOG);
        }
#endif

        return (Shader);
    }

    if (ShaderType == 2)
    {
        GLuint Shader = glCreateShader(GL_GEOMETRY_SHADER);

        const std::string &&ShaderSource = LoadShaderCode(Path);
        const char* Cstring = ShaderSource.c_str();

        glShaderSource(Shader, 1, &Cstring, NULL);
        glCompileShader(Shader);

#ifdef STANISZ_DEBUG
        int CompilationStatus;
        char InfoLOG[512];
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompilationStatus);

        if (CompilationStatus == GL_FALSE)
        {
            glGetShaderInfoLog(Shader, 512, NULL, InfoLOG);

            LOG("Geometry shader from path '" + (std::string)Path
                + "' compilation failed!\n" + (std::string)InfoLOG);
        }
#endif

        return (Shader);
    }

    return 0;
}

GLint CreateShaderProgram(const GLuint VertexShader,
                          const GLuint FragmentShader,
                          const GLuint GeometryShader)
{
    GLuint Program = glCreateProgram();

    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);

    if (GeometryShader != 0)
    {
        glAttachShader(Program, GeometryShader);
    }

    glLinkProgram(Program);

#ifdef STANISZ_DEBUG

    GLint LinkingStatus;
    char InfoLOG[512];

    glGetProgramiv(Program, GL_LINK_STATUS, &LinkingStatus);
    if(!LinkingStatus)
    {
        glGetProgramInfoLog(Program, 512, NULL, InfoLOG);
        LOG("Program linking failed!\n" + (std::string)InfoLOG);

        return (0);
    }
#endif

    return (Program);
}

void handlePressedKeys(GLFWwindow* window, std::map<int, bool>& keysPressed,
Sprite& player)
{
    if (keysPressed[GLFW_KEY_ESCAPE])
    {
        glfwSetWindowShouldClose(window, 1);
    }
    if (keysPressed[GLFW_KEY_W])
    {
        player.velocity += glm::fvec2(0, 1);
    }
    if (keysPressed[GLFW_KEY_S])
    {
        player.velocity += glm::fvec2(0, -1);
    }
    if (keysPressed[GLFW_KEY_A])
    {
        player.velocity += glm::fvec2(-1, 0);
    }
    if (keysPressed[GLFW_KEY_D])
    {
        player.velocity += glm::fvec2(1, 0);
    }
    if (keysPressed[GLFW_KEY_SPACE])
    {
        player.dashingSpeed = player.dashAffection * player.speed;
        player.dashingVector = player.velocity;
    }
}

void updatePlayerPositionAndVelocity(float dt, Sprite& player, const WindowData& windowData)
{
    player.isMoving = 0;

    if (player.velocity != glm::fvec2(0))
    {
        player.isMoving = 1;
    }
    if (player.velocity != glm::fvec2(0, 0))
    {
        player.velocity = glm::normalize(player.velocity);
    }
    if (player.dashingVector != glm::fvec2(0, 0))
    {
          player.dashingVector = glm::normalize(player.dashingVector);
    }

    if (player.dashingVector != player.velocity)
    {
        player.dashingSpeed = 0.0f;
    }

    if (player.dashingSpeed > 0.0001f)
    {
        player.dashingSpeed -= dt;
    }
    else
    {
        player.dashingSpeed = 0.0f;
    }

    glm::fvec2 aspectOffset = glm::fvec2(1.0f/windowData.aspectRatio, 1.0f);
    player.position += player.velocity * aspectOffset * dt * (player.speed + player.dashingSpeed);
}


void normalizeToScreen(glm::fvec2& v, const WindowData& windowData)
{
    v = {v.x / windowData.width, v.y / windowData.height};
}

void normalizeToScreen(float& w, float& h, const WindowData& windowData)
{
    w = w / windowData.width;
    h = h / windowData.height;
}

void CreateAndSetUpWindow(WindowData& windowData)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowData.contextVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowData.contextVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef FULLSCREEN
    windowData.pointer = glfwCreateWindow(windowData.width, windowData.height, windowData.name, NULL, NULL);
#else
    windowData.pointer = glfwCreateWindow(windowData.width, windowData.height, windowData.name, glfwGetPrimaryMonitor(), NULL);
#endif

    if (windowData.pointer == NULL)
    {
        LOG("Failed to create GLFW window!");

        return;
    }

    glfwGetWindowSize(windowData.pointer, &windowData.width, &windowData.height);

    glfwSetKeyCallback(windowData.pointer, key_callback);
    glfwSetFramebufferSizeCallback(windowData.pointer, resize_callback);

    glfwMakeContextCurrent(windowData.pointer);

    glfwSwapInterval(0);

    return;
}

void loadUniformLocations(DrawingEssentials& de)
{
    de.modelLoc = glGetUniformLocation(de.program, "model");
    de.texLoc = glGetUniformLocation(de.program, "theTexture");
    de.positionOfTexLoc = glGetUniformLocation(de.program, "positionOfTex");
    de.spritesPerDimensionsLoc = glGetUniformLocation(de.program, "spritesPerDimensions");
}

void setUpShaderProgramAndVAO(DrawingEssentials& de)
{
    GLuint VertexShader = CreateShader("src/shaders/basic.vs", 0);
    GLuint FragmentShader = CreateShader("src/shaders/basic.fs", 1);
    de.program = CreateShaderProgram(VertexShader, FragmentShader, 0);

    setUpBasicVAO(de.VAO);
}

 bool initializeGL(WindowData& windowData)
{
    if (glfwInit() != GL_TRUE)
    {
        LOG("Failed to initialize GLFW!");

        return 0;
    }

    CreateAndSetUpWindow(windowData);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG("Failed to initialize GLAD!");

        return 0;
    }

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 1;
}

bool initDrawingEssentials(DrawingEssentials& de,
WindowData& windowData)
{
    if (!initializeGL(windowData))
        return 0;

    setUpShaderProgramAndVAO(de);
    glUseProgram(de.program);
    glBindVertexArray(de.VAO);
    loadUniformLocations(de);

    return 1;
}

glm::fvec2 getBasicScaler(TextureData* data,
const WindowData& windowData)
{

    return {data->width / windowData.width, data->height / windowData.height};
}

glm::fvec2 getScaler(TextureData* data, const float& factor,
const WindowData& windowData)
{

    glm::fvec2 res = factor * getBasicScaler(data, windowData);
    data->width *= factor;
    data->height *= factor;

    return res;
}

void initTexture(TextureData* data, const char* path,
     int spritesInOneRow, int spritesInOneCollumn)
{
    data->path = path;
    data->spritesInOneRow = spritesInOneRow;
    data->spritesInOneCollumn = spritesInOneCollumn;
    loadTexture(data);
}

void initPlayer(Sprite& player,
const WindowData& windowData)
{
    player.texData = new TextureData;

    initSprite(player, "assets/walk.png", windowData.aspectRatio,
                9, 4);
    player.speed = 0.9;
    player.dashAffection = 1.8f;
    player.positionOfTex = glm::vec2(0, 2);     //facing downwards
    player.timeForOneAnimationFrame = 0.2f;
    player.box.position = player.position;
    player.scaler = getScaler(player.texData, 0.3f, windowData);
    player.box.size = player.scaler * 2.0f;
}

void initRocks(StaticObject rocks[], const int rocksCount,
const WindowData& windowData)
{
    TextureData* rockTexData = new TextureData;
    initTexture(rockTexData, "assets/white.jpg", 1, 1);

    for (int i = 0; i<rocksCount; ++i)
    {
        StaticObject& r = rocks[i];

        r.texData = new TextureData;
        *(r.texData) = *rockTexData;
    }

    glm::fvec2 s = getScaler(rockTexData, 0.3f, windowData);
    /*for (int i = 0; i<rocksCount; ++i)
    {
        StaticObject& r = rocks[i];

        r.texData = new TextureData;
        *(r.texData) = *rockTexData;

        float randW, randH;
        randW = rand()%(2*windowData.width) - windowData.width;
        randH = rand()%(2*windowData.height) - windowData.height;
        normalizeToScreen(randW, randH, windowData);

        r.position = glm::fvec2(randW, randH);
        r.scaler = s;
        r.model = glm::translate(glm::fmat4(1), glm::fvec3(r.position, 0.0));
        r.model = glm::scale(r.model, glm::fvec3(r.scaler, 0.0f));
        r.box.position = r.position;
        r.box.size = r.scaler * 2.0f;
    }*/

    StaticObject& r = rocks[0];
    r.position = glm::fvec2(0, 0);
    r.scaler = s;
    r.scaler.y = windowData.height / r.texData->height;
    r.scaler.x = windowData.width * 0.1f / r.texData->width;
    r.model = glm::translate(glm::fmat4(1), glm::fvec3(r.position, 0.0));
    r.model = glm::scale(r.model, glm::fvec3(r.scaler, 0.0f));
    r.box.position = r.position;
    r.box.size = r.scaler * 2.0f;
}

bool boundingBoxesCollide(const BoundingBox& a, const BoundingBox& b)
{
    glm::fvec2 p1 = {a.position.x - a.size.x/2, a.position.y - a.size.y/2};
    glm::fvec2 p2 = {b.position.x - b.size.x/2, b.position.y - b.size.y/2};

    bool collidesX = p1.x + a.size.x >= p2.x &&
        p2.x + b.size.x >= p1.x;

    bool collidesY = p1.y + a.size.y >= p2.y &&
        p2.y + b.size.y >= p1.y;

    return collidesX && collidesY;
}

void handlePlayerCollisions(Sprite& player, StaticObject rocks[],
const int rocksCount)
{
    player.box.position = player.position;
    for (int i = 0; i<rocksCount; ++i)
    {
        StaticObject& r = rocks[i];

        if (boundingBoxesCollide(player.box, r.box))
        {
            LOG("KARAMBOL XDD");
        }
        else
        {
            LOG("NIEEE");
        }
    }
}

void draw(const Sprite& s, const DrawingEssentials& de)
{
    glUniform2f(de.spritesPerDimensionsLoc, s.texData->spritesInOneRow, s.texData->spritesInOneCollumn);
    glUniform2f(de.positionOfTexLoc, s.positionOfTex.x, s.positionOfTex.y);
    glUniformMatrix4fv(de.modelLoc, 1, GL_FALSE, glm::value_ptr(s.model));

    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
}

void draw(const StaticObject& o, const DrawingEssentials& de)
{
    glUniform2f(de.spritesPerDimensionsLoc, 1, 1);
    glUniform2f(de.positionOfTexLoc, 0, 0);
    glUniformMatrix4fv(de.modelLoc, 1, GL_FALSE, glm::value_ptr(o.model));

    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
}

void draw(const Particle& p, const DrawingEssentials& de)
{
    glUniform2f(de.spritesPerDimensionsLoc, 1, 1);
    glUniform2f(de.positionOfTexLoc, 0, 0);
    glUniformMatrix4fv(de.modelLoc, 1, GL_FALSE, glm::value_ptr(p.model));

    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
}

void updatePlayerModel(Sprite& player)
{
    player.model = glm::translate(glm::mat4(1), glm::fvec3(player.position, 0));
    player.model = glm::scale(player.model, glm::fvec3(player.scaler, 0));
}

void updatePlayerAnimations(Sprite& player)
{
    if (player.velocity != player.movementLastFrame or player.animationTime >= player.timeForOneAnimationFrame)
    {
        if (player.velocity.x <= 0)
        {
            //goint left
            player.positionOfTex.y = 1;
        }
        else
        {
            //going right
            player.positionOfTex.y = 3;
        }

        if (player.velocity.x == 0)
        {
            if (player.velocity.y > 0)
            {
                //going up
                player.positionOfTex.y = 0;
            }
            else
            {
                //going down
                player.positionOfTex.y = 2;
            }
        }

        if (player.positionOfTex.x < player.texData->spritesInOneRow - 1)
        {
            player.positionOfTex.x++;
        }
        else
        {
            player.positionOfTex.x = 0;
        }

        player.animationTime = 0;
    }

    player.movementLastFrame = player.velocity;
    player.velocity = glm::fvec2(0);
}

void updatePlayer(const float dt, Sprite& player, const WindowData& windowData,
StaticObject rocks[], const int rocksCount)
{
    updatePlayerPositionAndVelocity(dt, player, windowData);
    handlePlayerCollisions(player, rocks, rocksCount);
    updatePlayerModel(player);
    updatePlayerAnimations(player);
}
