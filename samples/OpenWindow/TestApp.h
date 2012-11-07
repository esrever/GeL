#pragma once

#include <application/appbase.h>

class cTestApp : public cAppBase
{
public:
	virtual void InitGPU();
	virtual void DestroyGPU();
	virtual void InitCPU();
	virtual void DestroyCPU();
	virtual void Update(const cUpdateEvt&);
	virtual void Render(const cRenderEvt&);
	virtual void Resize(const cResizeEvt&);
};