#pragma once
#include <GL\glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "color.h"
using namespace std;

class Font
{
public:
    Font(FT_Face);
    ~Font();

    unsigned int getSize();
    void setSize(unsigned int);
    void renderText(string, float, float, Color);

    static float SX;
    static float SY;
private:
    FT_Face face;
    FT_GlyphSlot g; //pointer to face->glyph
    GLuint tex;
    GLuint vao;
    GLuint vbo;
    unsigned int size;
};