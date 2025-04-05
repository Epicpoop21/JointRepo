#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTextCoord;

out vec3 ourColor;
out vec2 textCoord;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    ourColor = vec3(1.0f, 0.0f, 0.0f);
    textCoord = aTextCoord;
}