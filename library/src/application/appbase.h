#pragma once

struct cUpdateEvt;
struct cRenderEvt;
struct cResizeEvt;
struct cMouseBtnEvt;
struct cMouseWheelEvt;
struct cMouseMoveEvt;
struct cKeyboardEvt;

class cAppBase
{
public:
	cAppBase();
	virtual ~cAppBase();

	virtual void InitCPU(){};
	virtual void InitGPU(){};
	virtual void DestroyCPU(){};
	virtual void DestroyGPU(){};
	virtual void Update(const cUpdateEvt&){};
	virtual void Render(const cRenderEvt&){};
	virtual void Resize(const cResizeEvt&){};
	virtual void MouseBtn(const cMouseBtnEvt&){};
	virtual void MouseMove(const cMouseMoveEvt&){};
	virtual void MouseWheel(const cMouseWheelEvt&){};
	virtual void Keyboard(const cKeyboardEvt&){};
};