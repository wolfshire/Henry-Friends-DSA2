#include "FreeImage.h"
#include "texturemanager.h"
#include <iostream>

TextureManager* TextureManager::instance = new TextureManager();

void TextureManager::init()
{
    #ifdef FREEIMAGE_LIB
        FreeImage_Initialise(true);
    #endif

    std::cout << "FreeImage version: " << FreeImage_GetVersion() << std::endl;
}

TextureManager::TextureManager()
{
    textures = std::map<std::string, Texture*>();
}

TextureManager::~TextureManager()
{
    #ifdef FREEIMAGE_LIB
        FreeImage_DeInitialise();
    #endif

    unloadAllTextures();
    instance = nullptr;
}

Texture* TextureManager::getTexture(std::string name)
{
    if (textures.find(name) == textures.end())
        loadTexture(name);

    return textures[name];
}

void TextureManager::loadTexture(std::string name)
{
    std::string path = TEX_DIR + name;
    const char* filename = path.c_str();

    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP *image(0);
    BYTE* bits(0);
    unsigned int width(0), height(0);

    std::cout << "Loading texture: " << filename << std::endl;

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    //if still unknown
    if (fif == FIF_UNKNOWN)
    {
        std::cout << "Unknown file format" << std::endl;
        //return;
    }

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
    {
        image = FreeImage_Load(fif, filename);
        //image = FreeImage_ConvertTo32Bits(image);
    }
    //if the image failed to load, use missing tex
    if (!image)
    {
        std::cout << "Error loading texture: " << filename << std::endl;
        const char* missName = (TEX_DIR + MISSING).c_str();
        image = FreeImage_Load(fif, missName);
        //image = FreeImage_ConvertTo32Bits(image);
        delete missName;
    }

    //retrieve the image data
    bits = FreeImage_GetBits(image);
    //get the image width and height
    width = FreeImage_GetWidth(image);
    height = FreeImage_GetHeight(image);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
    {
        std::cout << "Failed reading data for texture" << std::endl;
        return;
    }

    GLuint gl_texID;
    glGenTextures(1, &gl_texID);
    textures[name] = new Texture(gl_texID);
    glBindTexture(GL_TEXTURE_2D, gl_texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, bits);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //Free FreeImage's copy of the data
    FreeImage_Unload(image);
}

void TextureManager::unloadTexture(std::string name)
{
    if (textures.find(name) != textures.end())
    {
        glDeleteTextures(1, &textures[name]->m_nTextureID);
        textures.erase(name);
    }
}

void TextureManager::unloadAllTextures()
{
    //start at the begginning of the texture map
    std::map<std::string, Texture*>::iterator i = textures.begin();

    //Unload the textures untill the end of the texture map is found
    while (i != textures.end())
        unloadTexture(i->first);

    //clear the texture map
    textures.clear();
}