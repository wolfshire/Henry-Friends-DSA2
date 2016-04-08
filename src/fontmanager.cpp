#include <iostream>
#include "fontmanager.h"
using namespace std;

FontManager* FontManager::instance = new FontManager();

FontManager::FontManager()
{
    if (FT_Init_FreeType(&ft))
    {
        cout << "Unable to initialize freetype library." << endl;
        exit(1);
    }
}
FontManager::~FontManager() {}

void FontManager::init()
{
    load("anonymouspro-regular");
    load("freesans");
    load("techniclite");
}

Font* FontManager::getDefaultFont() { return instance->loadedFonts["anonymouspro-regular"]; }

Font* FontManager::getFont(string name)
{
    if (instance->loadedFonts[name] == NULL)
        load(name);

    return instance->loadedFonts[name];
}

void FontManager::load(string name)
{
    cout << "Loading font: " << name << endl;

    FT_Face face;
    string filename = "fonts\\" + name + ".ttf";
    const char* fname = filename.c_str();

    if (FT_New_Face(instance->ft, fname, 0, &face))
    {
        cout << "ERROR: Could not load font!" << endl;
        exit(2);
    }

    instance->loadedFonts[name] = new Font(face);

    cout << "Loaded!" << endl;
}