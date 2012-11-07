#include "TestApp.h"

#include <iostream>
using namespace std;

void cTestApp::InitGPU()
{
	cout<<"Initgpu"<<endl;
}

void cTestApp::DestroyGPU()
{
	cout<<"DEstroygpu"<<endl;
}

void cTestApp::InitCPU()
{
	cout<<"InitCpu"<<endl;
}

void cTestApp::DestroyCPU()
{
	cout<<"DEstroyCpu"<<endl;
}

void cTestApp::Update(const cUpdateEvt&)
{
	//cout<<"Update"<<endl;
}

void cTestApp::Render(const cRenderEvt&)
{
	//cout<<"Render"<<endl;
}

void cTestApp::Resize(const cResizeEvt&)
{
	cout<<"Resize"<<endl;
}
