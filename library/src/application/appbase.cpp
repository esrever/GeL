#include "appbase.h"
#include "glapp.h"

#include <windows.h>

namespace gel
{

	cAppBase::cAppBase()
	{
	#define CONNECT_BOILERPLATE(N) cGlapp::get_mutable_instance().sig##N##.Connect( this, &cAppBase::##N )
		CONNECT_BOILERPLATE(InitCPU);
		CONNECT_BOILERPLATE(InitGPU);
		CONNECT_BOILERPLATE(DestroyCPU);
		CONNECT_BOILERPLATE(DestroyGPU);
		CONNECT_BOILERPLATE(Update);
		CONNECT_BOILERPLATE(Render);
		CONNECT_BOILERPLATE(Resize);
		CONNECT_BOILERPLATE(MouseBtn);
		CONNECT_BOILERPLATE(MouseMove);
		CONNECT_BOILERPLATE(MouseWheel);
		CONNECT_BOILERPLATE(Keyboard);
	#undef CONNECT_BOILERPLATE

		char rootpath[MAX_PATH];
		GetEnvironmentVariableA("GELPATH",rootpath,MAX_PATH);
		mRootPath = rootpath;
	}

	cAppBase::~cAppBase()
	{
	#define DISCONNECT_BOILERPLATE(N) cGlapp::get_mutable_instance().sig##N##.Disconnect( this, &cAppBase::##N )
		DISCONNECT_BOILERPLATE(InitCPU);
		DISCONNECT_BOILERPLATE(InitGPU);
		DISCONNECT_BOILERPLATE(DestroyCPU);
		DISCONNECT_BOILERPLATE(DestroyGPU);
		DISCONNECT_BOILERPLATE(Update);
		DISCONNECT_BOILERPLATE(Render);
		DISCONNECT_BOILERPLATE(Resize);
		DISCONNECT_BOILERPLATE(MouseBtn);
		DISCONNECT_BOILERPLATE(MouseMove);
		DISCONNECT_BOILERPLATE(MouseWheel);
		DISCONNECT_BOILERPLATE(Keyboard);
	#undef DISCONNECT_BOILERPLATE	
	}
}