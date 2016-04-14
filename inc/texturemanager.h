#pragma once

#include <GL\glew.h>
#include <map>
#include "texture.h"

class TextureManager
{
public:
    static TextureManager* instance;

    Texture* GetTexture(std::string);

private:
    TextureManager();
    ~TextureManager();

    void LoadTexture(std::string);
    void UnloadTexture(std::string);
    void UnloadAllTextures();

    const std::string TEX_DIR = "textures\\";
    const std::string MISSING = "missing.png";

    std::map<std::string, Texture*> textures;
};