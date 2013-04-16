#include "DrawTests.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glcore/error.h>

#include "common.h"

#include <iostream>
using namespace std;


gel::cProgram shprog;

static const GLuint g_NumInstances = 16;
static GLuint g_ArrayBufferPos,g_ArrayBufferCol;
static GLuint g_ElementArrayBuffer;
static GLuint g_VertexArray;
static GLuint g_UniformMVP;
static GLuint g_UniformBuffer;
static GLuint g_UniformBlockLoc;

#define DO_INIT draw_noattribs_init
#define DO_RENDER draw_noattribs_render
#define DO_DESTROY draw_noattribs_destroy

//------------------------------------------------------------------
static void draw_indexed_init()
{
	g_ArrayBufferPos = CreateBuffer(GL_ARRAY_BUFFER, PositionSize, (void *)PositionData, GL_STATIC_DRAW);
	g_ArrayBufferCol = CreateBuffer(GL_ARRAY_BUFFER, ColorSize, (void *)ColorData, GL_STATIC_DRAW);
	g_ElementArrayBuffer = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementSize, (void *)ElementData, GL_STATIC_DRAW);


	g_VertexArray = cVertexArrayCreator().Add<glm::vec3>(eVertexAttrib::ATTR_POS,g_ArrayBufferPos)
		.Add<glm::u8vec4>(eVertexAttrib::ATTR_COL,g_ArrayBufferCol)
		.Elements(g_ElementArrayBuffer).mId;
	LoadShader("draw",shprog);
}

static void draw_indexed_render()
{
	// Order of bind buffer/ va doesn't matter
	glBindVertexArray(g_VertexArray);
	glDrawElements(GL_TRIANGLES,g_NumElements,GL_UNSIGNED_INT,0);
}

static void draw_indexed_destroy()
{
	glDeleteBuffers(1, &g_ArrayBufferPos);
	glDeleteBuffers(1, &g_ArrayBufferCol);
	glDeleteBuffers(1, &g_ElementArrayBuffer);
	glDeleteVertexArrays(1, &g_VertexArray);	
}

//------------------------------------------------------------------
static void draw_indexed_instanced_init()
{
	// Vertex array and buffers
	g_ArrayBufferPos = CreateBuffer(GL_ARRAY_BUFFER, PositionSize, (void *)PositionData, GL_STATIC_DRAW);
	g_ArrayBufferCol = CreateBuffer(GL_ARRAY_BUFFER, ColorSize, (void *)ColorData, GL_STATIC_DRAW);
	g_ElementArrayBuffer = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementSize, (void *)ElementData, GL_STATIC_DRAW);


	g_VertexArray = cVertexArrayCreator().Add<glm::vec3>(eVertexAttrib::ATTR_POS,g_ArrayBufferPos)
		.Add<glm::u8vec4>(eVertexAttrib::ATTR_COL,g_ArrayBufferCol)
		.Elements(g_ElementArrayBuffer).mId;
	LoadShader("draw_instanced",shprog);
	glBindVertexArray(0);


	// Uniform buffer
	GLint UniformBufferOffset(0);
	glGetIntegerv(
		GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
		&UniformBufferOffset);

	GLint UniformBlockSize = glm::max(GLint(sizeof(glm::mat4) * g_NumInstances), UniformBufferOffset);
	g_UniformBuffer = CreateBuffer(GL_UNIFORM_BUFFER, UniformBlockSize, NULL, GL_DYNAMIC_DRAW);
	g_UniformBlockLoc = glGetUniformBlockIndex(shprog.Id(), "instanceData");

	// Uniform buffer data

	glBindBuffer(GL_UNIFORM_BUFFER, g_UniformBuffer);
	glm::mat4* xforms = (glm::mat4*)glMapBufferRange(
		GL_UNIFORM_BUFFER, 0,	sizeof(glm::mat4) * g_NumInstances,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for(unsigned i=0;i<g_NumInstances;++i)
	{
		xforms[i] = glm::translate(glm::vec3(3*(i&3),3*(i>>2),50));
	}

	// Make sure the uniform buffer is uploaded
	glUnmapBuffer(GL_UNIFORM_BUFFER);
}

static void draw_indexed_instanced_render()
{
	GLint binding;
	glGetActiveUniformBlockiv(shprog.Id(),g_UniformBlockLoc, GL_UNIFORM_BLOCK_BINDING, &binding);
	gel::checkError("glUniformBlockBinding");
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, g_UniformBuffer);
	gel::checkError("glBindBufferBase");

	// Order of bind buffer/ va doesn't matter
	glBindVertexArray(g_VertexArray);
	glDrawElementsInstanced(GL_TRIANGLES,g_NumElements,GL_UNSIGNED_INT,0, g_NumInstances);
}
static void draw_indexed_instanced_destroy()
{
	glDeleteBuffers(1, &g_ArrayBufferPos);
	glDeleteBuffers(1, &g_ArrayBufferCol);
	glDeleteBuffers(1, &g_ElementArrayBuffer);
	glDeleteVertexArrays(1, &g_VertexArray);	
}


//------------------------------------------------------------------
static void draw_noattribs_init()
{
	g_ElementArrayBuffer = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementSize, (void *)ElementData, GL_STATIC_DRAW);
	g_VertexArray = cVertexArrayCreator().Elements(g_ElementArrayBuffer).mId;
	//g_VertexArray = cVertexArrayCreator().mId;
	LoadShader("draw_noattribs_instanced",shprog);
	glBindVertexArray(0);


	// Uniform buffer
	GLint UniformBufferOffset(0);
	glGetIntegerv(
		GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
		&UniformBufferOffset);

	GLint UniformBlockSize = glm::max(GLint(sizeof(glm::mat4) * g_NumInstances), UniformBufferOffset);
	g_UniformBuffer = CreateBuffer(GL_UNIFORM_BUFFER, UniformBlockSize, NULL, GL_DYNAMIC_DRAW);
	g_UniformBlockLoc = glGetUniformBlockIndex(shprog.Id(), "instanceData");

	// Uniform buffer data

	glBindBuffer(GL_UNIFORM_BUFFER, g_UniformBuffer);
	glm::mat4* xforms = (glm::mat4*)glMapBufferRange(
		GL_UNIFORM_BUFFER, 0,	sizeof(glm::mat4) * g_NumInstances,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	for(unsigned i=0;i<g_NumInstances;++i)
	{
		xforms[i] = glm::translate(glm::vec3(3*(i&3),3*(i>>2),50));
	}

	// Make sure the uniform buffer is uploaded
	glUnmapBuffer(GL_UNIFORM_BUFFER);
}

static void draw_noattribs_render()
{
	GLint binding;
	glGetActiveUniformBlockiv(shprog.Id(),g_UniformBlockLoc, GL_UNIFORM_BLOCK_BINDING, &binding);
	gel::checkError("glUniformBlockBinding");
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, g_UniformBuffer);
	gel::checkError("glBindBufferBase");

	// Order of bind buffer/ va doesn't matter
	glBindVertexArray(g_VertexArray);
	//glDrawArraysInstanced(GL_TRIANGLES,0,g_NumElements,g_NumInstances);
	glDrawElementsInstanced(GL_TRIANGLES,g_NumElements,GL_UNSIGNED_INT,0, g_NumInstances);
}

static void draw_noattribs_destroy()
{
	glDeleteBuffers(1, &g_ElementArrayBuffer);
	glDeleteVertexArrays(1, &g_VertexArray);	
}


void cDrawTests::InitGPU()
{
	DO_INIT();
	int param=0;
	glGetProgramiv(shprog.Id(),GL_ACTIVE_UNIFORMS,&param);
	g_UniformMVP = glGetUniformLocation(shprog.Id(), "MVP");
	glBindAttribLocation(shprog.Id(), ATTR_POS, "Position");
	glBindAttribLocation(shprog.Id(), ATTR_COL, "Color");
	glBindFragDataLocation(shprog.Id(), 0, "Color");
	shprog.Link();
	return;
}

void cDrawTests::DestroyGPU()
{
	DO_DESTROY();
	shprog.Del();
}

void cDrawTests::Render(const gel::cRenderEvt&)
{
	// Compute the MVP (Model View Projection matrix)
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 4.0f, 0.1f, 100.0f);
	glm::vec3 eye = glm::vec3(0,0,-13);
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

	DO_RENDER();

	// Unbind program
	glUseProgram(0);
}

