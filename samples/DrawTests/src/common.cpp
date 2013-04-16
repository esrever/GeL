#include "common.h"

#include <application/appbase.h>
#include <glcore/error.h>
#include <shader/program.h>

void LoadShader(const std::string& base,gel::cProgram& prog)
{
	const std::string fullpath = gel::cAppBase::get_const_instance().RootPath() + "\\samples\\media\\shaders\\";

	gel::cShader<GL_VERTEX_SHADER> shvert;
	gel::cShader<GL_FRAGMENT_SHADER> shfrag;
	shvert.Gen();
	shvert.LoadTextFile(fullpath + base + ".vert");
	gel::checkError(".vert compilation error");
	shfrag.Gen();
	shfrag.LoadTextFile(fullpath + base + ".frag");
	gel::checkError(".frag compilation error");
	prog.Gen();
	prog.Attach(shvert);
	prog.Attach(shfrag);
	prog.Link();
}

GLuint CreateBuffer(GLenum target, GLsizei dataSize, void * data, GLenum mode)
{
	GLuint bufName;
	glGenBuffers(1,&bufName);
	glBindBuffer(target, bufName);
	glBufferData(target, dataSize, data, mode);
	gel::checkError("buffer_creation_error");

	return bufName;
}