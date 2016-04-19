#pragma once

#include <GL\glew.h>
#include <map>
#include "texture.h"

class TextureManager
{
public:
    static TextureManager* instance;

    static void init();
    Texture* getTexture(std::string);

private:
    TextureManager();
    ~TextureManager();

    void loadTexture(std::string);
    void unloadTexture(std::string);
    void unloadAllTextures();

    const std::string TEX_DIR = "textures\\";
    const std::string MISSING = "missing.png";

    std::map<std::string, Texture*> textures;
};