#version 400

uniform sampler2D tex;

in vec2 uv;
out vec4 gl_FragColor;

void main()
{
    //gl_FragColor = texture2D(tex, uv);
    gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}