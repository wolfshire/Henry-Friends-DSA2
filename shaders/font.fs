#version 400

in vec2 texcoord;
uniform sampler2D tex;
uniform vec4 color;

out vec4 gl_FragColor;

void main()
{
    gl_FragColor = vec4(1, 1, 1, texture2D(tex, texcoord).r) * color;
}