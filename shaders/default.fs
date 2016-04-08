#version 400

in vec2 uvCoord;

uniform sampler2D tex;

out vec4 gl_FragColor;

void main()
{
    gl_FragColor = texture(tex, uvCoord);
}