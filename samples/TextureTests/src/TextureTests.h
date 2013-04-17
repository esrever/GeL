#pragma once

#include <application/appbase.h>

#include <shader/shader.h>
#include <shader/program.h>

class cTextureTests : public gel::cAppBase
{
public:
	virtual void InitGPU();
	virtual void DestroyGPU();
	virtual void InitCPU(){}
	virtual void DestroyCPU(){}
	virtual void Update(const gel::cUpdateEvt&){}
	virtual void Render(const gel::cRenderEvt&);
	virtual void Resize(const gel::cResizeEvt&);

	void LoadTexture(const std::string& zFilename);
	bool LoadImageData(const std::string& zFilename);
	bool LoadDDS(const std::string& zFilename);

private:

};