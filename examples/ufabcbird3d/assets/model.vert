#version 300 es

layout(location = 0) in vec3 inPosition;

uniform vec4 color;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec4 fragColor;

void main() {
    //Posição no espaço da camera
    vec4 posEyeSpace = viewMatrix * modelMatrix * vec4(inPosition, 1);

    float i = 1.0 - (-posEyeSpace.z / 10.);
    fragColor = color ;//* vec4(i, i, i, 1.);

    gl_Position = projMatrix * posEyeSpace;
}