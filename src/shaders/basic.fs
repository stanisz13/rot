#version 330 core

in vec2 texCoords;

uniform sampler2D theTexture;

uniform vec2 positionOfTex;
uniform vec2 spritesPerDimensions;

out vec4 FragColor;

void main()
{
    float spritesInOneRow = spritesPerDimensions.x;
    float spritesInOneCollumn = spritesPerDimensions.y;
    
    vec2 cellSize = vec2(texCoords.x / spritesInOneRow, (1-texCoords.y)/ spritesInOneCollumn);
    vec2 newTexCoords =  cellSize +  positionOfTex * vec2(1/spritesInOneRow, 1/spritesInOneCollumn);


    vec4 t = texture(theTexture, newTexCoords);
   
    FragColor = t;
}
