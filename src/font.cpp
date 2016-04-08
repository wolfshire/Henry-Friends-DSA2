#include <GL\glew.h>
#include "font.h"
#include "shadermanager.h"
#include <iostream>
using namespace std;
float Font::SX = 0;
float Font::SY = 0;

Font::Font(FT_Face _face)
{
    face = _face;
    g = face->glyph;

    Shader* shader = ShaderManager::getShader("font");
    shader->addUniform("tex");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(shader->getUniformLocation("tex"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

Font::~Font() {}

float Font::getSize() { return size; }

void Font::setSize(float _size)
{
    size = _size;
    FT_Set_Pixel_Sizes(face, 0, size);
}

void Font::renderText(string text, float x, float y, Color c)
{
    Shader* shader = ShaderManager::getShader("font");
    GLuint uniLoc = shader->getUniformLocation("color");

    glUseProgram(shader->getProgram());
    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    for (int i = 0; i < text.length(); i++)
    {
        if (FT_Load_Char(face, text[i], FT_LOAD_RENDER))
            continue;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows,
            0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        float x2 = x + g->bitmap_left * SX;
        float y2 = -y - g->bitmap_top * SY;
        float w = g->bitmap.width * SX;
        float h = g->bitmap.rows * SY;

        GLfloat box[4][4] = 
        {
            {x2    , -y2    , 0, 0},
            {x2 + w, -y2    , 1, 0},
            {x2    , -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1}
        };

        //cout << x2 << "," << -y2 << " | " << (x2 + w) << "," << -y2 << " | ";
        //cout << x2 << "," << (-y2 - h) << " | " << (x2 + w) << "," << (-y2 - h) << endl;

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);

        GLfloat color[4] = { c.r, c.g, c.b, c.a };
        glUniform4fv(uniLoc, 1, color);
        glPointSize(1.0f);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        x += (g->advance.x >> 6) * SX;
        y += (g->advance.y >> 6) * SY;
    }
}