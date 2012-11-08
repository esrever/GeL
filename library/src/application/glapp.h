#pragma once

#include <boost/serialization/singleton.hpp>

#include "classdecl.h"
#include <signals/signal.h>

using Gallant::Signal0;
using Gallant::Signal1;


namespace gel
{
	struct cUpdateEvt;
	struct cRenderEvt;
	struct cResizeEvt;
	struct cMouseBtnEvt;
	struct cMouseMoveEvt;
	struct cMouseWheelEvt;
	struct cKeyboardEvt;

	class cGlapp : public boost::serialization::singleton<cGlapp>
	{
	public:
		// Signals
		Signal0<void> sigInitCPU;
		Signal0<void> sigInitGPU;
		Signal0<void> sigDestroyCPU;
		Signal0<void> sigDestroyGPU;
		Signal1<const cUpdateEvt&> sigUpdate;
		Signal1<const cRenderEvt&> sigRender;
		Signal1<const cResizeEvt&> sigResize;
		Signal1<const cMouseBtnEvt&> sigMouseBtn;
		Signal1<const cMouseWheelEvt&> sigMouseWheel;
		Signal1<const cMouseMoveEvt&> sigMouseMove;
		Signal1<const cKeyboardEvt&> sigKeyboard;

		// Construction
		cGlapp();
		virtual ~cGlapp();

		// Accessible interface
	
		DECL_RO_VAR(float,CurFrame)

		// These two go to update event
		DECL_RO_VAR(float,ElapsedTime)
		DECL_RO_VAR(float,TotalTime)

		//ScreenDims : ResizeEvt, accessible as is

		//DefaultCam
		//DefaultCRT
		//DefaultDRT

	protected:

	private:

	};
}