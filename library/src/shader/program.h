#pragma once

#include <glcore/globj.h>

#include "shader.h"

namespace gel
{
	class cProgram : public cGlObj<cProgram>
	{
	public:
		DECL_RW_VAR_REF(std::string, Name);
		template<GLenum S>
		void Attach( cShader<S> zShader) { glAttachShader(Id(), zShader.Id());}
		void Link();

		void Use(bool zVal = true) { glUseProgram( zVal ? Id() : 0);}

	private:
		// GLobj iface
		friend class cGlObj< cProgram >;
		static bool Valid(unsigned zId) { return glIsProgram(zId) ? true : false;}
		static unsigned Gen() { return glCreateProgram();}
		static void Del(unsigned zId) { glDeleteProgram(zId);}
	};

}