#version 400
layout (location = 0) in vec3 pos;

uniform mat4 worldMatrix;

void main()
{
    gl_Position = worldMatrix * vec4(pos, 1.0);
}