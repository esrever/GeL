#pragma once

#include <cassert>
#include <GL/glew.h>

namespace gel
{

	template<GLuint T>
	class cGlid
	{
		public:
			cGlid(bool gen = false):mId(0) { if(gen) Gen();}
			~cGlid() { if(mId) Del();}
			GLuint Id() const { return mId; }

			void Gen(){ assert(0); }
			void Del(){ assert(0); }
			GLboolean Valid() const { return false; }

		private:
			GLuint mId;
	};

	// Buffer
	template<> void cGlid<GL_BUFFER>::Gen() { glGenBuffers(1,&mId); }
	template<> void cGlid<GL_BUFFER>::Del() { glDeleteBuffers(1,&mId); }
	template<> GLboolean cGlid<GL_BUFFER>::Valid() const { return glIsBuffer(mId); }

	// Vertex Array
	template<> void cGlid<GL_VERTEX_ARRAY>::Gen() { glGenVertexArrays(1,&mId); }
	template<> void cGlid<GL_VERTEX_ARRAY>::Del() { glDeleteVertexArrays(1,&mId); }
	template<> GLboolean cGlid<GL_VERTEX_ARRAY>::Valid() const { return glIsVertexArray(mId); }

	// Shaders
	#define SHADER_BOILERPLATE( S ) \
	template<> void cGlid<GL_##S##_SHADER>::Gen() { mId = glCreateShader(GL_##S##_SHADER);}\
	template<> void cGlid<GL_##S##_SHADER>::Del() { glDeleteShader(mId); }\
	template<> GLboolean cGlid<GL_##S##_SHADER>::Valid() const { return glIsShader(mId); }

	SHADER_BOILERPLATE(VERTEX)
	SHADER_BOILERPLATE(FRAGMENT)
	SHADER_BOILERPLATE(GEOMETRY)
	SHADER_BOILERPLATE(TESS_EVALUATION)
	SHADER_BOILERPLATE(TESS_CONTROL)
	
	#undef SHADER_BOILERPLATE

	// Shader program
	template<> void cGlid<GL_PROGRAM>::Gen() { mId = glCreateProgram(); }
	template<> void cGlid<GL_PROGRAM>::Del() { glDeleteProgram(mId); }
	template<> GLboolean cGlid<GL_PROGRAM>::Valid() const { return glIsProgram(mId); }

}