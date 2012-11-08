#pragma once

namespace gel
{
	enum eMouseBtn
	{
		MouseBtnLeft,
		MouseBtnRight,
		MouseBtnMiddle,
		MouseBtnWheel
	};

	struct cResizeEvt
	{
		int w;
		int h;
	};

	struct cRenderEvt
	{
		int window;
	};

	struct cUpdateEvt
	{
	};

	struct cKeyboardEvt
	{
		int key;
		bool up;
		bool special;
		int x,y;
	};

	struct cMouseBtnEvt
	{
		eMouseBtn btn;
		bool up;
	};

	struct cMouseMoveEvt
	{
		int x,y;
	};

	struct cMouseWheelEvt
	{
		int wheelIndex;
		int direction;
	};
}