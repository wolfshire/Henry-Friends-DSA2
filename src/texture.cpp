#include <iostream>
#include "texture.h"
using namespace std;

Texture::Texture(GLuint texID)
{
	m_nTextureID = texID;
}

Texture::~Texture()
{
    
}

GLuint Texture::getId() { return m_nTextureID; }

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_nTextureID);
}

void Texture::LoadTexture(string a_sFileName)
{
	m_sFileName = a_sFileName;

	if (a_sFileName == "NULL")
		return;

	/*
	m_sName = a_sFileName;
	m_sFileName = m_pSystem->m_pFolder->GetFolderRoot();
	m_sFileName += m_pSystem->m_pFolder->GetFolderData();
	m_sFileName += m_pSystem->m_pFolder->GetFolderTextures();
	m_sFileName += m_sName;
	*/
	//Based on Raul's implementation: http://www.raul-art.blogspot.com
	FREE_IMAGE_FORMAT eFormat = FreeImage_GetFileType(m_sFileName.c_str(), 0);//Detect the file format
	FIBITMAP* image = FreeImage_Load(eFormat, m_sFileName.c_str()); //Load the file as FreeImage imagefile
	image = FreeImage_ConvertTo32Bits(image); //convert to 32bits

	int w = FreeImage_GetWidth(image);
	int h = FreeImage_GetHeight(image);

	GLubyte* tempGLTexture = new GLubyte[4 * w * h];//Create a new texture to hold the information onto
	char* pixeles = (char*)FreeImage_GetBits(image);//Create a pixel container
													//FreeImage loads in BGRA format, so you need to swap some bytes (Or use GL_BGR).
	for (int nPixel = 0; nPixel < (w * h); nPixel++)
	{
		tempGLTexture[nPixel * 4 + 0] = pixeles[nPixel * 4 + 2];
		tempGLTexture[nPixel * 4 + 1] = pixeles[nPixel * 4 + 1];
		tempGLTexture[nPixel * 4 + 2] = pixeles[nPixel * 4 + 0];
		tempGLTexture[nPixel * 4 + 3] = pixeles[nPixel * 4 + 3];
	}
	FreeImage_Unload(image); //RE_DONE with the image, unload it

	if (m_nTextureID > 0)// if the texture is already binded
	{
		glDeleteTextures(1, &m_nTextureID);
	}

	//Now generate the OpenGL texture object 
	glGenTextures(1, &m_nTextureID); //Generate a container
	glBindTexture(GL_TEXTURE_2D, m_nTextureID); //Set the active texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)tempGLTexture); //Set the data
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //set parameters

	if (glGetError())
	{
		std::cout << "There was an error loading the texture" << std::endl;
	}
}