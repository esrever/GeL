#include "SimpleGeom.h"

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

static GLuint g_VertexArray;

static GLuint g_SimpleElementNum;


static GLuint g_ProgramName;
static GLuint g_UniformMVP;

void cSimpleGeom::InitGPU()
{
	g_SimpleElementNum = g_NumElements;
	std::vector<glm::vec3> posSimple(g_NumElements);
	std::vector<glm::u8vec4> colSimple(g_NumElements);
	std::vector<glm::vec4> fcolSimple(g_NumElements);

	for(GLuint i=0;i<g_SimpleElementNum;++i)
	{
		posSimple.at(i) = PositionData[ElementData[i]];
		colSimple.at(i) = ColorData[ElementData[i]];
		fcolSimple.at(i) = fColorData[ElementData[i]];
	}

	glGenBuffers(1,&g_ArrayBufferPos);
	glBindBuffer(GL_ARRAY_BUFFER, g_ArrayBufferPos);
	glBufferData(GL_ARRAY_BUFFER, g_SimpleElementNum*sizeof(glm::vec3), &posSimple.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	gel::checkError("ArrayBufferPos");

	glGenBuffers(1,&g_ArrayBufferCol);
	glBindBuffer(GL_ARRAY_BUFFER, g_ArrayBufferCol);
	glBufferData(GL_ARRAY_BUFFER, g_SimpleElementNum*sizeof(glm::u8vec4), &colSimple.front(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, g_SimpleElementNum*sizeof(glm::vec4), &fcolSimple.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	gel::checkError("ArrayBufferCol");

	glGenVertexArrays(1,&g_VertexArray);

	glBindVertexArray(g_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, g_ArrayBufferPos);
	glVertexAttribPointer(eVertexAttrib::ATTR_POS, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(eVertexAttrib::ATTR_POS);

	glBindBuffer(GL_ARRAY_BUFFER, g_ArrayBufferCol);
	glVertexAttribPointer(eVertexAttrib::ATTR_COL, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(glm::u8vec4), BUFFER_OFFSET(0));
	//glVertexAttribPointer(eVertexAttrib::ATTR_COL, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(eVertexAttrib::ATTR_COL);

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

	glBindAttribLocation(shprog.Id(), ATTR_POS, "Position");
	glBindAttribLocation(shprog.Id(), ATTR_COL, "Color");
	glBindFragDataLocation(shprog.Id(), 0, "Color");

	gel::checkError("shprog");

	g_ProgramName = shprog.Id();

	g_UniformMVP = glGetUniformLocation(shprog.Id(), "MVP");

	gel::checkError("uniform");

	return;
}

void cSimpleGeom::DestroyGPU()
{
	glDeleteBuffers(1, &g_ArrayBufferPos);
	glDeleteBuffers(1, &g_ArrayBufferCol);
	glDeleteVertexArrays(1, &g_VertexArray);	

	shvert.Del();
	shfrag.Del();
	shprog.Del();
}

void cSimpleGeom::Render(const cRenderEvt&)
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 4.0f, 0.1f, 100.0f);
	glm::vec3 eye = glm::vec3(0,0,-7);
	glm::vec3 center = glm::vec3(0,0,0);
	glm::vec3 up = glm::vec3(0,1,0);
	glm::mat4 View = glm::lookAt(eye,center,up);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	// Set the display viewport
	glViewport(0, 0, 1024, 1024);
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
	//glDrawArrays(GL_TRIANGLES, 0, g_SimpleElementNum);
	glDrawArraysInstanced(GL_TRIANGLES, 0, g_SimpleElementNum, 16);
	gel::checkError("DrawArrays");

	// Unbind program
	glUseProgram(0);
}

