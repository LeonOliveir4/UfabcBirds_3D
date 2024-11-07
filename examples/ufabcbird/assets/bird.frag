#version 300 es

precision mediump float;

flat in int fragColorIndex;

out vec4 outColor;

void main() { 
    if (fragColorIndex == 0) {
        outColor = vec4(1.0,0.843, 0.0, 1.0);
    }else if (fragColorIndex == 1) {
        outColor = vec4(1.0,0.439, 0.0, 1.0);
    }else if (fragColorIndex == 2) {
        outColor = vec4(1.0,1.0, 1.0, 1.0);
    }else if (fragColorIndex == 3) {
        outColor = vec4(0.0,0.0, 0.0, 1.0);
    }else if (fragColorIndex == 4) {
        outColor = vec4(0.0,0.0, 0.0, 1.0);
    }else {
        outColor = vec4(0.2, 0.2, 0.2, 1.0);
    }
}