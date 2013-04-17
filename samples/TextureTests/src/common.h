#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

GLsizei const g_NumElements(6);
GLsizeiptr const ElementSize = g_NumElements * sizeof(glm::uint32);
glm::uint32 const ElementData[g_NumElements] =
{
	0, 1, 2,
	0, 2, 3
};

GLsizei const VertexCount(8);
GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec3);
glm::vec3 const PositionData[VertexCount] =
{
	glm::vec3(-1.0f,-1.0f, 0.5f),
	glm::vec3( 1.0f,-1.0f, 0.5f),
	glm::vec3( 1.0f, 1.0f, 0.5f),
	glm::vec3(-1.0f, 1.0f, 0.5f),
	glm::vec3(-0.5f,-1.0f,-0.5f),
	glm::vec3( 0.5f,-1.0f,-0.5f),
	glm::vec3( 1.5f, 1.0f,-0.5f),
	glm::vec3(-1.5f, 1.0f,-0.5f)
};

GLsizeiptr const ColorSize = VertexCount * sizeof(glm::u8vec4);
glm::u8vec4 const ColorData[VertexCount] =
{
	glm::u8vec4(255,   0,   0, 255),
	glm::u8vec4(255, 255,   0, 255),
	glm::u8vec4(  0, 255,   0, 255),
	glm::u8vec4(  0,   0, 255, 255),
	glm::u8vec4(255, 128, 128, 255),
	glm::u8vec4(255, 255, 128, 255),
	glm::u8vec4(128, 255, 128, 255),
	glm::u8vec4(128, 128, 255, 255)
};

GLsizeiptr const fColorSize = VertexCount * sizeof(glm::vec4);
glm::vec4 const fColorData[VertexCount] =
{
	glm::vec4(1,   0.1,   0.1, 1),
	glm::vec4(1, 1,   0.1, 1),
	glm::vec4(  0.1, 1,   0.1, 1),
	glm::vec4(  0.1,   0.1, 1, 1),
	glm::vec4(1, 0.5, 0.5, 1),
	glm::vec4(1, 1, 0.5, 1),
	glm::vec4(0.5, 1, 0.5, 1),
	glm::vec4(0.5, 0.5, 1, 1)
};

enum eVertexAttrib
{
	ATTR_POS = 0,
	ATTR_COL = 1
};

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// Utility functions

namespace gel
{
	class cProgram;
}

void LoadShader(const std::string& base, gel::cProgram& prog);
unsigned CreateBuffer(GLenum target, GLsizei dataSize, void * data, GLenum mode);

template<typename T>
struct cVertexAttribParams
{
    static const GLuint components = 0;
    static const GLuint type = 0;
    static const GLuint normalize = 0;
};

#define VATTR_BOILERPLATE( A, B, C, D) \
template<> struct cVertexAttribParams< A >{ \
static const GLuint components = B ; \
static const GLuint type = C ; \
static const GLuint normalize = D ; };


VATTR_BOILERPLATE( float , 1 , GL_FLOAT, GL_FALSE)
VATTR_BOILERPLATE( glm::vec2 , 2 , GL_FLOAT, GL_FALSE)
VATTR_BOILERPLATE( glm::vec3 , 3 , GL_FLOAT, GL_FALSE)
VATTR_BOILERPLATE( glm::vec4 , 4 , GL_FLOAT, GL_FALSE)
VATTR_BOILERPLATE( unsigned , 1 , GL_UNSIGNED_INT, GL_FALSE)
VATTR_BOILERPLATE( glm::uvec2 , 2 , GL_UNSIGNED_INT, GL_FALSE)
VATTR_BOILERPLATE( glm::uvec3 , 3 , GL_UNSIGNED_INT, GL_FALSE)
VATTR_BOILERPLATE( glm::uvec4 , 4 , GL_UNSIGNED_INT, GL_FALSE)
VATTR_BOILERPLATE( double , 1 , GL_DOUBLE, GL_FALSE)
VATTR_BOILERPLATE( glm::dvec2 , 2 , GL_DOUBLE, GL_FALSE)
VATTR_BOILERPLATE( glm::dvec3 , 3 , GL_DOUBLE, GL_FALSE)
VATTR_BOILERPLATE( glm::dvec4 , 4 , GL_DOUBLE, GL_FALSE)

VATTR_BOILERPLATE( glm::u8vec4 , 4 , GL_UNSIGNED_BYTE, GL_TRUE)

#undef VATTR_BOILERPLATE


struct cVertexArrayCreator
{
	cVertexArrayCreator(){ glGenVertexArrays(1,&mId);glBindVertexArray(mId);}
 
	template<typename T>
	cVertexArrayCreator&  Add(GLuint attribLocation, GLuint bufferId)
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glVertexAttribPointer(attribLocation,  cVertexAttribParams<typename T>::components, 
											   cVertexAttribParams<typename T>::type, 
											   cVertexAttribParams<typename T>::normalize, sizeof(T), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(attribLocation);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return *this;
	}
	
	cVertexArrayCreator&  Elements(GLuint bufferId)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
		return *this;
	}

	GLuint mId;
};
