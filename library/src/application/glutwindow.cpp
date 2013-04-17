#include "glutwindow.h"

//#include <boost/chrono.hpp>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include <application/glapp.h>
#include <application/events.h>

#include <AntTweakBar.h>

using namespace std;
//using namespace boost::chrono;

//--------------------------------------------------------------------------
namespace gel
{
	// static glut functions that signal the glapp stuff
	static void Reshape(int w, int h)
	{
		cResizeEvt evt;
		evt.w = w;
		evt.h = h;
		cGlapp::get_mutable_instance().sigResize(evt);
		glutPostRedisplay();
	}

	static void Display(void)
	{
		cRenderEvt evt;
		evt.window = glutGetWindow ();
		cGlapp::get_mutable_instance().sigRender(evt);
		glutSwapBuffers();
	}

	static void Idle(void)
	{
		cUpdateEvt evt;
		// TODO: get time from boost::chrono here. if first time, set to zero
		//static high_resolution_clock clock;
		//cout<<clock.now()<<endl;
		cGlapp::get_mutable_instance().sigUpdate(evt);
		glutPostRedisplay();
	}

	static void Key(unsigned char key, int x, int y)
	{
		TwEventKeyboardGLUT(key,x,y);
		if(key==27) {glutLeaveMainLoop();return;}
		cKeyboardEvt evt;
		evt.key = key;
		evt.special = false;
		evt.up = false;
		evt.x = x;
		evt.y = y;
		cGlapp::get_mutable_instance().sigKeyboard(evt);
		glutPostRedisplay();
	}

	static void Special(int key, int x, int y)
	{
		TwEventSpecialGLUT(key,x,y);
		cKeyboardEvt evt;
		evt.key = key;
		evt.special = true;
		evt.up = false;
		evt.x = x;
		evt.y = y;
		cGlapp::get_mutable_instance().sigKeyboard(evt);
		glutPostRedisplay();
	}

	static void KeyUp(unsigned char key, int x, int y)
	{
		cKeyboardEvt evt;
		evt.key = key;
		evt.special = false;
		evt.up = true;
		evt.x = x;
		evt.y = y;
		cGlapp::get_mutable_instance().sigKeyboard(evt);
		glutPostRedisplay();
	}

	static void SpecialUp(int key, int x, int y)
	{
		cKeyboardEvt evt;
		evt.key = key;
		evt.special = true;
		evt.up = true;
		evt.x = x;
		evt.y = y;
		cGlapp::get_mutable_instance().sigKeyboard(evt);
		glutPostRedisplay();
	}

	static void Mouse(int button, int updown, int x, int y)
	{
		TwEventMouseButtonGLUT(button,updown,x,y);
		cMouseBtnEvt evt;
		cMouseMoveEvt mevt;
		switch (button)
		{
			case GLUT_LEFT_BUTTON: evt.btn = eMouseBtn::MouseBtnLeft;break;
			case GLUT_RIGHT_BUTTON: evt.btn = eMouseBtn::MouseBtnRight;break;
			case GLUT_MIDDLE_BUTTON: evt.btn = eMouseBtn::MouseBtnMiddle;break;
			default:
				break;
		}
		evt.up = updown ? true : false;
		mevt.x = x;
		mevt.y = y;
		cGlapp::get_mutable_instance().sigMouseBtn(evt);
		cGlapp::get_mutable_instance().sigMouseMove(mevt);
		glutPostRedisplay();
	}

	static void Motion(int x, int y)
	{
		TwEventMouseMotionGLUT(x,y);
		cMouseMoveEvt evt;
		evt.x = x;
		evt.y = y;
		cGlapp::get_mutable_instance().sigMouseMove(evt);
		glutPostRedisplay();
	}

	static void PassiveMotion(int x, int y)
	{
		TwEventMouseMotionGLUT(x,y);
		cMouseMoveEvt evt;
		evt.x = x;
		evt.y = y;
		cGlapp::get_mutable_instance().sigMouseMove(evt);
		glutPostRedisplay();
	}

	static void 
	MouseWheel(int wheel_number, int direction, int x, int y)
	{
		cMouseWheelEvt evt;
		cMouseMoveEvt mevt;
		evt.wheelIndex = wheel_number;
		evt.direction = direction;
		mevt.x = x;
		mevt.y = y;
		cGlapp::get_mutable_instance().sigMouseWheel(evt);
		cGlapp::get_mutable_instance().sigMouseMove(mevt);
		glutPostRedisplay();
	}

	static void Close()
	{
		TwTerminate();
		cGlapp::get_mutable_instance().sigDestroyGPU();
		cGlapp::get_mutable_instance().sigDestroyCPU();
	}

	//--------------------------------------------------------------------------
	//--------------------------------------------------------------------------
	cGlutWindow::cCreationParams::cCreationParams()
		:mDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL),
		mContextVersion(3,2),
		mContextFlags(GLUT_FORWARD_COMPATIBLE),
		mContextProfile(GLUT_CORE_PROFILE),
		mWindowPosition(100,100),
		mWindowSize(600,600),
		mWindowTitle("Test")
	{
	}

	//--------------------------------------------------------------------------
	void cGlutWindow::Create(int argc, char ** argv, const cCreationParams& params)
	{
		GLenum err;

		glutInit(&argc, argv);
		glutInitDisplayMode(params.mDisplayMode);
		glutInitContextVersion(params.mContextVersion.x,params.mContextVersion.y);
		glutInitContextFlags(params.mContextFlags);
		glutInitContextProfile(params.mContextProfile);
		glutInitWindowPosition(params.mWindowPosition.x, params.mWindowPosition.y);
		glutInitWindowSize(params.mWindowSize.x, params.mWindowSize.y);
		glutCreateWindow(params.mWindowTitle.c_str());

		TwInit(TW_OPENGL_CORE, NULL);

		glewExperimental=TRUE;
		err=glewInit();
		if(err!=GLEW_OK)
		{
			//Problem: glewInit failed, something is seriously wrong.
			cout<<"glewInit failed, aborting."<<endl;
			exit(-1);
		}

		// Need this to clear the buffer from the weird error
		err = glGetError();

		const GLubyte * versionStr = glGetString(GL_VERSION);
		cout<<"OpenGL version: "<<versionStr<<endl;

		/*
		glm::ivec2 version;
		glGetIntegerv(GL_MAJOR_VERSION,&version.x);
		glGetIntegerv(GL_MINOR_VERSION,&version.y);
		cout<<"OpenGL version: "<<version.x<<"."<<version.y<<endl;
		*/

		// Set functions
		glutDisplayFunc(Display); 
		glutReshapeFunc(Reshape);
		glutIdleFunc ( Idle );
		glutKeyboardFunc( Key );
		glutKeyboardUpFunc( KeyUp );
		glutSpecialFunc( Special );
		glutSpecialUpFunc( SpecialUp );
		glutMouseFunc ( Mouse ) ;
		glutMouseWheelFunc ( MouseWheel ) ;
		glutMotionFunc ( Motion ) ;
		glutPassiveMotionFunc ( PassiveMotion ) ;
		glutCloseFunc ( Close ) ;
		TwGLUTModifiersFunc(glutGetModifiers);


		// Now that we've loaded GL, initialize gpu resources
		cGlapp::get_mutable_instance().sigInitGPU();

		glutMainLoop();
	}
}