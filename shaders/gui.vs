#version 400
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 inUV;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec2 uv;

void main()
{
    gl_Position = proj * (view * (model * vec4(pos, -5, 1.0)));
    //gl_Position = vec4(pos, -5, 1.0);
    uv = inUV;
}