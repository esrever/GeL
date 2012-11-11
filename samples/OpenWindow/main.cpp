#include <application/glutwindow.h>
#include <application/glapp.h>

#include "TestApp.h"

#include <core/blob.h>
#include <glcore/globj.h>

using namespace gel;

int main(int argc, char ** argv)
{
	cTestApp app;

	// Init cpu-related data first
	cGlapp::get_mutable_instance().sigInitCPU();


	// Run CPU tests
	app.TestAll();

	// Open the window and run it
	cGlutWindow win;
	cGlutWindow::cCreationParams params;
	params.mContextVersion = glm::ivec2(4,2);
	win.Create(argc,argv,params);

	// Destroy cpu-related data last
	cGlapp::get_mutable_instance().sigDestroyCPU();
}