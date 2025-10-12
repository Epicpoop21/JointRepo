#version 440 core

out vec4 FragColor;

uniform vec4 colorValue;
uniform bool circle;
uniform float radius;       // Radius in pixels (e.g. 200.0)
uniform vec2 centre;        // Centre in pixels (e.g. vec2(960.0, 540.0))

void main()
{
    if (circle) {
        float dist = distance(vec2(gl_FragCoord.x, gl_FragCoord.y), centre);
        if (dist > radius) {
            discard;
        }
    }


    FragColor = vec4(gl_FragCoord.x / 1920.0f, 0.0f, 0.5f, 1.0f);
}