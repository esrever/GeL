#pragma once

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

enum eVertexAttrib
{
	ATTR_POS = 0,
	ATTR_COL = 1
};

#define BUFFER_OFFSET(i) ((char *)NULL + (i))