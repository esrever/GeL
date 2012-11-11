#pragma once

#include <GL/glew.h>

namespace gel
{
	// GL object base. Every wrapping class can use this.
	template<class T>
	class cGlObj
	{
	public:
		cGlObj()			{ mId = T::Gen(); }
		virtual ~cGlObj()	{ T::Del(mId); }
		
		GLuint Id() const		{ return mId; }
		void SetId( GLuint zId)	{ mId = zId; }

		virtual bool IsValid() const {return T::Valid(mId);}
		
	private:
		GLuint mId;
	};
}