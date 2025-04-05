#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 textCoord;

uniform bool useBlack;
uniform sampler2D ourTexture;

void main()
{
    if (useBlack) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Draw lines as black
    } else {
        FragColor = texture(ourTexture, textCoord); // Draw the texture normally
    }
} 