#pragma once

#include <glcore/globj.h>

#include "shader.h"

namespace gel
{
	class cProgram : public cGlid<GL_PROGRAM>
	{
	public:
		DECL_RW_VAR_REF(std::string, Name);
		template<GLenum S>
		void Attach( cShader<S> zShader) { glAttachShader(Id(), zShader.Id());}
		void Link();

		void Use(bool zVal = true) const { glUseProgram( zVal ? Id() : 0);}
	};

}