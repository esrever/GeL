#include "program.h"

namespace gel
{
	void cProgram::Link()
	{
		glLinkProgram(Id());

		int infolen;
		glGetProgramiv(Id(),GL_INFO_LOG_LENGTH,&infolen);
		if(infolen)
		{
			std::vector<char> text(infolen);
			glGetProgramInfoLog(Id(),infolen,NULL,&text.front());
			std::string errstr(text.begin(),text.end());
		}
	}
}