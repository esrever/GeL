#include "TextureTests.h"

#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gli/gli.hpp>

#include <AntTweakBar.h>
#include <FreeImage.h>

#include <application/events.h>
#include <utility/fileutils.h>
#include <math/pot.h>
#include <glcore/error.h>

#include "common.h"

#include <iostream>
using namespace std;


gel::cProgram shprog;

static const GLuint g_NumInstances = 16;
static GLuint g_ElementArrayBuffer;
static GLuint g_VertexArray;
static GLuint g_CurTextureUnit=0;
static const unsigned MAX_TEXTURE_UNITS = 8;
static GLuint g_TextureNames[MAX_TEXTURE_UNITS];

static const unsigned MAX_SAMPLERS = 2;
static GLuint g_SamplerNames[MAX_SAMPLERS];
static GLuint g_CurSampler;
static const TwEnumVal sSamplerId[] = // array used to describe the Scene::AnimMode enum values
{
	{ 0, "nearest"	 }, 
	{ 1, "linear"    }
};

void TW_CALL LoadImageCB(void *clientData)
{
	std::vector<std::string> files = gel::OpenFileDialog("Image files\0*.jpg;*.png;*.tiff;*.dds;*.bmp;*.tif;\0All Files\0*.*\0");
	if(!files.empty())
	{
		cTextureTests * app = (cTextureTests *)clientData;
		app->LoadTexture(files.front());
	}
}


void cTextureTests::InitGPU()
{
	// Init textures & samplers
	glGenTextures(MAX_TEXTURE_UNITS,g_TextureNames);
	glGenSamplers(MAX_SAMPLERS,g_SamplerNames);

	// Init sampler data
	glSamplerParameteri(g_SamplerNames[0],GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glSamplerParameteri(g_SamplerNames[0],GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glSamplerParameteri(g_SamplerNames[1],GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glSamplerParameteri(g_SamplerNames[1],GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	// Create a tweak bar
	TwBar *bar;
	bar = TwNewBar("TweakBar");
	TwDefine(" GLOBAL help='You are helpless, dude' "); // Message added to the help bar.
	TwDefine(" TweakBar size='200 400' color='96 216 224' "); // change default tweak bar size and color
	TwAddButton(bar,"Load Image",LoadImageCB,this,"");
	TwAddVarRW(bar, "CurrentTextureUnit", TW_TYPE_UINT32, &g_CurTextureUnit, 
		" label='Current Texture Unit'  min=0 max=7 ");
	TwType samplerType = TwDefineEnum("SamplerType", sSamplerId, MAX_SAMPLERS);
	TwAddVarRW(bar, "Samplers", samplerType, &g_CurSampler, "");

	// Create the quad data
	g_ElementArrayBuffer = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementSize, (void *)ElementData, GL_STATIC_DRAW);
	g_VertexArray = cVertexArrayCreator().Elements(g_ElementArrayBuffer).mId;
	LoadShader("texture_test",shprog);
	glBindVertexArray(0);
	glBindFragDataLocation(shprog.Id(), 0, "Color");
	shprog.Link();


	LoadTexture(RootPath() + "\\samples\\media\\textures\\RGB24.jpg");
	//LoadTexture(RootPath() + "\\contrib\\ogl-samples-4.3.2.1\\data\\kueken3-bgr8.dds");

	return;
}

void cTextureTests::DestroyGPU()
{
	glDeleteTextures(MAX_TEXTURE_UNITS,g_TextureNames);
	glDeleteSamplers(MAX_SAMPLERS,g_SamplerNames);
	glDeleteBuffers(1, &g_ElementArrayBuffer);
	glDeleteVertexArrays(1, &g_VertexArray);
	shprog.Del();
}

void cTextureTests::Render(const gel::cRenderEvt&)
{
	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind program
	glUseProgram(shprog.Id());

	GLuint textureLoc = glGetUniformLocation(shprog.Id(), "image");
	glUniform1i(textureLoc, g_CurTextureUnit); //Texture unit 0 is for base images.
	
	glActiveTexture(GL_TEXTURE0 + g_CurTextureUnit);
	glBindTexture(GL_TEXTURE_2D, g_TextureNames[g_CurTextureUnit]);
	glBindSampler(g_CurTextureUnit, g_SamplerNames[g_CurSampler]);

	glBindVertexArray(g_VertexArray);
	glDrawElementsInstanced(GL_TRIANGLES,g_NumElements,GL_UNSIGNED_INT,0, g_NumInstances);

	// Unbind program
	glUseProgram(0);
	glBindSampler(g_CurTextureUnit, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	TwDraw();
}

void cTextureTests::Resize(const gel::cResizeEvt& evt)
{
	TwWindowSize(evt.w, evt.h);
	glViewport(0,0,evt.w,evt.h);
}

void cTextureTests::LoadTexture(const std::string& zFilename)
{
	glActiveTexture(GL_TEXTURE0 + g_CurTextureUnit);
	glBindTexture(GL_TEXTURE_2D, g_TextureNames[g_CurTextureUnit]);

	LoadImageData(zFilename);
	//LoadDDS(zFilename);
}

bool cTextureTests::LoadImageData(const std::string& zFilename)
{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0), *dibconv(0);

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(zFilename.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(zFilename.c_str());
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, zFilename.c_str());
	//if the image failed to load, return failure
	if(!dib)
		return false;

	//retrieve the image data
	unsigned width = FreeImage_GetWidth(dib);
	unsigned height = FreeImage_GetHeight(dib);
	unsigned bpp = FreeImage_GetBPP(dib);
	FREE_IMAGE_COLOR_TYPE ctype = FreeImage_GetColorType(dib);

	unsigned components = 0;
	unsigned textureFormat = 0;
	unsigned internalFormat = 0;
	switch(ctype)
	{
		case FIC_MINISBLACK:
		case FIC_MINISWHITE:
			components = 1;
			internalFormat = GL_RED;
			textureFormat = GL_RED;
			dibconv = FreeImage_ConvertToGreyscale(dib);
			break;
		case FIC_PALETTE:
		case FIC_RGB:
			components = 3;
			internalFormat = GL_RGB;
			textureFormat = GL_BGR;
			dibconv = FreeImage_ConvertTo24Bits(dib);
			break;
		case FIC_RGBALPHA:
		case FIC_CMYK:
			components = 4;
			internalFormat = GL_RGBA;
			textureFormat = GL_BGRA;
			dibconv = FreeImage_ConvertTo32Bits(dib);
			break;
	}
	FreeImage_Unload(dib);

	BYTE* bits = FreeImage_GetBits(dibconv);

	unsigned levels = gel::pot::NearestPowUp(std::max(width,height))+1;

	// GetBits returns 16-bit aligned data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height,
		0, textureFormat, GL_UNSIGNED_BYTE, bits);
	gel::checkError("LoadTexture");
	glGenerateMipmap(GL_TEXTURE_2D);
	gel::checkError("GenMipmaps");

	//Free FreeImage's copy of the data
	FreeImage_Unload(dibconv);

	glutReshapeWindow(width,height);
	
	return true;
}

bool cTextureTests::LoadDDS(const std::string& zFilename)
{
	gli::texture2D Texture(gli::loadStorageDDS(zFilename));
	gel::checkError("LoadDDSFile");

	glTexStorage2D(GL_TEXTURE_2D, GLint(Texture.levels()), GL_RGBA8UI, GLsizei(Texture.dimensions().x), GLsizei(Texture.dimensions().y));
	gel::checkError("SetStorage");
	for(gli::texture2D::size_type Level = 0; Level < Texture.levels(); ++Level)
	{
		glTexSubImage2D(
			GL_TEXTURE_2D, 
			GLint(Level), 
			0, 0, 
			GLsizei(Texture[Level].dimensions().x), 
			GLsizei(Texture[Level].dimensions().y), 
			GL_BGR_INTEGER, GL_UNSIGNED_BYTE, 
			Texture[Level].data());
	}
	gel::checkError("SetStorage");

	return true;
}