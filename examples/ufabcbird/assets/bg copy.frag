#version 300 es

precision mediump float;

in vec4 fragColor;
in vec2 resolution;
out vec4 outColor;
//gl_FragCoord
void main() { outColor = fragColor; }