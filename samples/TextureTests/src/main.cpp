#include <application/glutwindow.h>
#include <application/glapp.h>

#include "TextureTests.h"


using namespace gel;

int main(int argc, char ** argv)
{
	cTextureTests app;
	// Init cpu-related data first
	cGlapp::get_mutable_instance().sigInitCPU();

	// Open the window and run it
	cGlutWindow win;
	cGlutWindow::cCreationParams params;
	params.mWindowSize = glm::ivec2(1024,1024);
	params.mContextVersion = glm::ivec2(4,2);
	win.Create(argc,argv,params);

	// Destroy cpu-related data last
	cGlapp::get_mutable_instance().sigDestroyCPU();
}