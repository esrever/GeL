#include "IndexedGeom.h"

#include <file/filehelper.h>
#include <glcore/error.h>
#include <resource/buffer.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "common.h"

#include <iostream>
using namespace std;
using namespace gel;


static GLuint g_ArrayBufferPos,g_ArrayBufferCol;
static GLuint g_ElementArrayBuffer;


static GLuint g_VertexArray;

//gel::cBuffer g_ArrayBufferPos,g_ArrayBufferCol,g_ElementArrayBuffer;


static GLuint g_ProgramName;
static GLuint g_UniformMVP;

void cIndexedGeom::InitGPU()
{
	glGenBuffers(1,&g_ArrayBufferPos);
	glGenBuffers(1,&g_ArrayBufferCol);
	glGenBuffers(1,&g_ElementArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_ArrayBufferPos);
	glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);

	gel::checkError("ArrayBufferPos");

	glBindBuffer(GL_ARRAY_BUFFER, g_ArrayBufferCol);
	glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	gel::checkError("ArrayBufferCol");

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementArrayBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	gel::checkError("ElArrayBuffer");

	glGenVertexArrays(1,&g_VertexArray);

	glBindVertexArray(g_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, g_ArrayBufferPos);
	glVertexAttribPointer(eVertexAttrib::ATTR_POS, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(eVertexAttrib::ATTR_POS);

	glBindBuffer(GL_ARRAY_BUFFER, g_ArrayBufferCol);
	glVertexAttribPointer(eVertexAttrib::ATTR_COL, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(glm::u8vec4), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(eVertexAttrib::ATTR_COL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	gel::checkError("VertexArray");

	//glVertexAttrib4f(glf::semantic::attr::COLOR, 1.0f, 0.5f, 0.0f, 1.0f);

	glBindVertexArray(0);

	gel::checkError("ShaderInit");

	shvert.Gen();
	shvert.LoadTextFile(RootPath() + "\\samples\\media\\shaders\\simple_geom.vert");
	gel::checkError("shvert");
	shfrag.Gen();
	shfrag.LoadTextFile(RootPath() + "\\samples\\media\\shaders\\simple_geom.frag");
	gel::checkError("shfrag");
	shprog.Gen();
	shprog.Attach(shvert);
	shprog.Attach(shfrag);
	shprog.Link();

	int param=0;
	glGetProgramiv(shprog.Id(),GL_ACTIVE_UNIFORMS,&param);
	g_UniformMVP = glGetUniformLocation(shprog.Id(), "MVP");

	glBindAttribLocation(shprog.Id(), ATTR_POS, "Position");
	glBindAttribLocation(shprog.Id(), ATTR_COL, "Color");
	glBindFragDataLocation(shprog.Id(), 0, "Color");

	gel::checkError("shprog");

	g_ProgramName = shprog.Id();

	gel::checkError("uniform");

	return;
}

void cIndexedGeom::DestroyGPU()
{
	glDeleteBuffers(1, &g_ArrayBufferPos);
	glDeleteBuffers(1, &g_ArrayBufferCol);
	glDeleteBuffers(1, &g_ElementArrayBuffer);
	glDeleteVertexArrays(1, &g_VertexArray);	

	shvert.Del();
	shfrag.Del();
	shprog.Del();
}

void cIndexedGeom::Render(const cRenderEvt&)
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 4.0f, 0.1f, 100.0f);
	glm::vec3 eye = glm::vec3(0,0,-3);
	glm::vec3 center = glm::vec3(0,0,0);
	glm::vec3 up = glm::vec3(0,1,0);
	glm::mat4 View = glm::lookAt(eye,center,up);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Set the display viewport
	glViewport(0, 0, 600, 600);
	gel::checkError("Viewport");

	// Clear color buffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gel::checkError("Clear");

	// Bind program
	glUseProgram(shprog.Id());

	gel::checkError("UseProg");

	// Set the value of MVP uniform.
	glUniformMatrix4fv(g_UniformMVP, 1, GL_FALSE, &MVP[0][0]);

	gel::checkError("Uniform");

	// Order of bind buffer/ va doesn't matter
	glBindVertexArray(g_VertexArray);

	gel::checkError("BindVertArray");
	//glDrawElements(GL_TRIANGLES,g_NumElements,GL_UNSIGNED_INT,0);
	glDrawElementsInstanced(GL_TRIANGLES,g_NumElements,GL_UNSIGNED_INT,0, 16);
	//glDrawElementsInstancedBaseInstance(GL_TRIANGLES,g_NumElements,GL_UNSIGNED_INT,0, 16,1);
	gel::checkError("DrawElements");

	// Unbind program
	glUseProgram(0);
}

