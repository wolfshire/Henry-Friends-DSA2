#version 400

in vec2 uvCoord;

uniform sampler2D tex;

out vec4 gl_FragColor;

void main()
{
    gl_FragColor = texture2D(tex, uvCoord);
    //gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}