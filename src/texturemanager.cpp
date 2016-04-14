#include "FreeImage.h"
#include "texturemanager.h"
#include <iostream>

TextureManager* TextureManager::instance = new TextureManager();

TextureManager::TextureManager()
{
    #ifdef FREEIMAGE_LIB
        FreeImage_Initialise();
    #endif

    textures = std::map<std::string, Texture*>();
}

TextureManager::~TextureManager()
{
    #ifdef FREEIMAGE_LIB
        FreeImage_DeInitialise();
    #endif

    UnloadAllTextures();
    instance = nullptr;
}

Texture* TextureManager::GetTexture(std::string name)
{
    if (textures.find(name) == textures.end())
        LoadTexture(name);

    return textures[name];
}

void TextureManager::LoadTexture(std::string name)
{
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE* bits(0);
    //image width and height
    unsigned int width(0), height(0);
    //OpenGL's image ID to map to
    GLuint gl_texID;
    std::string path = TEX_DIR + name;
    const char* filename = path.c_str();

    std::cout << "Loading texture: " << filename << std::endl;

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    //if still unkown, return failure
    if (fif == FIF_UNKNOWN)
    {
        std::cout << "Unknown file format" << std::endl;
        //return;
    }

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
    {
        dib = FreeImage_Load(fif, filename);
    }
    //if the image failed to load, return failure
    if (!dib)
    {
        std::cout << "Error loading texture: " << filename << std::endl;
        const char* missName = (TEX_DIR + MISSING).c_str();
        dib = FreeImage_Load(fif, missName);
        delete missName;
    }

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
    {
        std::cout << "Failed reading data for texture" << std::endl;
        return;
    }

    //generate an OpenGL texture ID for this texture
    glGenTextures(1, &gl_texID);
    //store the texture ID mapping
    textures[name] = new Texture(gl_texID);
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, gl_texID);
    //store the texture data for OpenGL use
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
        0, GL_BGR, GL_UNSIGNED_BYTE, bits);

    //Free FreeImage's copy of the data
    FreeImage_Unload(dib);
}

void TextureManager::UnloadTexture(std::string name)
{
    if (textures.find(name) != textures.end())
    {
        glDeleteTextures(1, &textures[name]->m_nTextureID);
        textures.erase(name);
    }
}

void TextureManager::UnloadAllTextures()
{
    //start at the begginning of the texture map
    std::map<std::string, Texture*>::iterator i = textures.begin();

    //Unload the textures untill the end of the texture map is found
    while (i != textures.end())
        UnloadTexture(i->first);

    //clear the texture map
    textures.clear();
}