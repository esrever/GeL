#include <file/filehelper.h>

namespace gel
{
	template<GLenum S>
	void cShader<S>::LoadTextFile(const std::string& zFilename)
	{
		cFileHelper helper;
		std::string source;
		helper.ReadTextFile(zFilename, source);
		Load(source);
	}

	template<GLenum S>
	void cShader<S>::LoadBinFile(const std::string& zFilename)
	{
		// TODO: dep. on the extension, use appr format to call LoadMem
	}

	template<GLenum S>
	void cShader<S>::Load(const std::string& zText)
	{
		const char * textPtr = zText.c_str();
		int textLen = int(zText.size());
		glShaderSource(Id(),1,&textPtr, &textLen);
		// TODO: associate shader id, shader type with given source code
		Compile();
	}

	template<GLenum S>
	void cShader<S>::Load(const cBlob& zBlob, GLenum zBinaryFormat)
	{
		unsigned id[1] = {Id()};
		glShaderBinary(1, id,zBinaryFormat,zBlob.Data(), zBlob.Length());
		Compile();
	}

	template<GLenum S>
	void cShader<S>::Compile() 
	{
		glCompileShader(Id());
		int infolen;
		glGetShaderiv(Id(),GL_INFO_LOG_LENGTH,&infolen);
		if(infolen)
		{
			std::vector<char> text(infolen);
			glGetShaderInfoLog(Id(),infolen,NULL,&text.front());
			std::string errstr(text.begin(),text.end());
		}
	}


	template<GLenum S>
	void cShader<S>::GetParam(GLenum zParam, int* zVar)
	{
		glGetShaderiv(Id(),zParam,zVar);
	}
}

