#pragma once

#include <application/appbase.h>

class cTestApp : public gel::cAppBase
{
public:
	virtual void InitGPU();
	virtual void DestroyGPU();
	virtual void InitCPU();
	virtual void DestroyCPU();
	virtual void Update(const gel::cUpdateEvt&);
	virtual void Render(const gel::cRenderEvt&);
	virtual void Resize(const gel::cResizeEvt&);

	void TestAll();

	void TestGPU();

private:
	void testFileHelper();
	void testCamera();
};