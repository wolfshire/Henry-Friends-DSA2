#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <unordered_map>
#include "font.h"
using namespace std;
class FontManager
{
public:
    static void init();
    static Font* getDefaultFont();
    static Font* getFont(string);

    static FontManager* instance;
private:
    static void load(string);

    FontManager();
    ~FontManager();

    FT_Library ft;
    unordered_map<string, Font*> loadedFonts;
};