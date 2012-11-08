#pragma once

#include <Windows.h>
#include <GL/GL.h>

namespace gel
{
	// GL object base. Every wrapping class can use this.
	class cGlObj
	{
	public:
		cGlObj()			{ Gen(); }
		virtual ~cGlObj()	{ Del(); }
		
		GLuint Id() const		{ return mId; }
		void SetId( GLuint zId)	{ mId = zId; }

	protected:
		virtual void Gen()	{ mId = 0xFFFFFFFF; }
		virtual void Del()	{ };
		
	private:
		GLuint mId;
	};
}