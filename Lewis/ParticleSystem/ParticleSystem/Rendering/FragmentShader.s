#version 440 core

uniform vec3 colour;

uniform bool circle;
uniform float radius;
uniform vec2 circleCentres[1000];
uniform int numberOfCircles;

out vec4 FragColor;

void main() {
	bool insideCircle = false;
	for (int i = 0; i < numberOfCircles; i++) {
		if (pow(circleCentres[i].x - gl_FragCoord.x, 2.0) + pow(circleCentres[i].y - gl_FragCoord.y, 2.0) <= pow(radius, 2.0)) {
			insideCircle = true;
			break;
		}
	}
		
	if (insideCircle) {
		FragColor = vec4(0.0f, 1.0f, 0.5f, 1.0f);
	} else {	
		FragColor = vec4(colour, 1.0f);
	}

}