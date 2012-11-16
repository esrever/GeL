#pragma once

#include <glcore\globj.h>

namespace gel
{
	class cVao : public cGlObj<cVao>
	{
	public:
	public:
		static GLuint Gen()			{ GLuint id; glGenVertexArrays(1,&id); return id; }
		static void Del(GLuint zId)	{ glDeleteVertexArrays(1,&zId); }
	private:
	};
}