#version 300 es

layout (location = 0) in vec2 inPosition;
layout (location = 1) in int inColorIndex;

uniform float scale;
uniform bool flap;
uniform vec2 translation;

flat out int fragColorIndex;
void main() {
    vec2 newPosition = inPosition;
    if(flap == true && inColorIndex == 4) {
        if( inPosition == vec2(-0.52f,0.44f)) { //Z
            newPosition = vec2(-0.2f,-0.5f);
        }if( inPosition == vec2(-0.06,0.61f)) { //Z2
            newPosition = vec2(0.18f,-0.52f);
        }if( inPosition == vec2(-0.51f,0.19f)) { //W
            newPosition = vec2(-0.37f,-0.26f);
        }if( inPosition == vec2(-0.08f,0.23f)) { //V
            newPosition = vec2(-0.07f, 0.08f);
        }
    }
    newPosition = newPosition * scale + translation;
    gl_Position = vec4(newPosition, 0, 1);
    fragColorIndex= inColorIndex;
}