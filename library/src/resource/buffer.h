#pragma once

#include <vector>
#include <glcore/globj.h>

namespace gel
{
	class cBuffer : public cGlid<GL_BUFFER>
	{
		public:
			template<class T>			
			void SetData(GLenum target,
						 std::vector<T>& data,
 						 GLenum  		usage);

			void SetData(GLenum target,
						 GLsizeiptr		size,
 						 const GLvoid * data,
 						 GLenum  		usage);

		private:

	};
}


namespace gel
{
	template<class T>
	void cBuffer::SetData(GLenum target,
							 std::vector<typename T>& data,
 							 GLenum  		usage)
	{
		SetData(target, data.size() * sizeof(T::value_type), &data.front(), usage);
	}

}