#version 300 es

precision mediump float;

uniform vec2 resolution;
uniform mediump float time;
out vec4 outColor;

float noise(vec2 pq)
{
    return fract(sin(pq.x* 124.3 + pq.y * 215.4) * 3244.44 );
}

float noiseSmooth(vec2 pq)
{
    vec2 index = floor(pq);
    vec2 frag = fract(pq);
    frag = smoothstep(0.0, 1.0, frag);
    
   
    float topLeft = noise(index);
    float topRight = noise(index + vec2(1,0));
    float top = mix(topLeft, topRight, frag.x);
    
    float bottomLeft = noise(index + vec2(0,1));
    float bottomRight = noise(index + vec2(1,1));
    float bottom = mix(bottomLeft, bottomRight, frag.x);
    
    
    return mix(top, bottom, frag.y);
}



void main(){
    vec2 uv = gl_FragCoord.xy / vec2(800,800);
    //uv.x *= resolution.x / resolution.y;
    uv.x += time / 10.;
    uv.y -= 0.7;


    vec3 sky = vec3(0.5, 0.7, 0.85);
    // Time varying pixel color
    vec3 col = vec3(noiseSmooth(uv*4.0)) * 0.5;
    col += vec3(noiseSmooth(uv*8.)) * 0.25;
    col += vec3(noiseSmooth(uv*16.)) * 0.125;
    col += vec3(noiseSmooth(uv*32.)) * 0.075;
    col += vec3(noiseSmooth(uv*64.)) * 0.0375;
    col /= 2.;
    col -= uv.y - 0.6;
    col = smoothstep(0.333, 0.9,col);
    // Output to screen
    
    col = mix(vec3(1.f), sky, col);
    outColor = vec4(col,1.0f);
}
