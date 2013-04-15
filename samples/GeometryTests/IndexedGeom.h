#pragma once

#include <application/appbase.h>

#include <shader/shader.h>
#include <shader/program.h>

class cIndexedGeom : public gel::cAppBase
{
public:
	virtual void InitGPU();
	virtual void DestroyGPU();
	virtual void InitCPU(){}
	virtual void DestroyCPU(){}
	virtual void Update(const gel::cUpdateEvt&){}
	virtual void Render(const gel::cRenderEvt&);
	virtual void Resize(const gel::cResizeEvt&){}

private:

	gel::cShader<GL_VERTEX_SHADER> shvert;
	gel::cShader<GL_FRAGMENT_SHADER> shfrag;
	gel::cProgram shprog;

};