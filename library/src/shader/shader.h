#pragma once

#include <string>

#include <application/classdecl.h>
#include <core/blob.h>
#include <glcore/globj.h>


namespace gel
{
	/*
		A shader for a specific stage ( vertex, pixel,geometry, etc)
	*/
	template<GLenum S>
	class cShader : public cGlObj< cShader<S> >
	{
	public:

		DECL_RW_VAR_REF(std::string, Name);
		void Compile();
		
		void LoadTextFile(const std::string& zFilename);
		void LoadBinFile(const std::string& zFilename);
		void Load(const std::string& zText);
		void Load(const cBlob& zBlob, GLenum zBinaryFormat);

		void GetParam(GLenum zParam, int* zVar);
		
		/* // TODO
			void ReleaseShaderCompiler( void );
			GetShaderPrecisionFormat
		*/

	private:
		// GLobj iface
		friend class cGlObj< cShader<S> >;
		static bool Valid(unsigned zId) { return glIsShader(zId) ? true : false;}
		static unsigned Gen() { return glCreateShader(S);}
		static void Del(unsigned zId) { glDeleteShader(zId);}

	private:
	};
}

#include "shader.hpp"
