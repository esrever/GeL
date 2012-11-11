#include "TestApp.h"

#include <file/filehelper.h>
#include <shader/shader.h>
#include <shader/program.h>

#include <iostream>
using namespace std;
using namespace gel;

void cTestApp::InitGPU()
{
	cout<<"InitGpu"<<endl;

	TestGPU();
}

void cTestApp::DestroyGPU()
{
	cout<<"DestroyGpu"<<endl;
}

void cTestApp::InitCPU()
{
	cout<<"InitCpu"<<endl;
}

void cTestApp::DestroyCPU()
{
	cout<<"DestroyCpu"<<endl;
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


//-------------------------------------------
void cTestApp::TestAll()
{
	testFileHelper();
}

//-------------------------------------------
void cTestApp::testFileHelper()
{
	gel::cFileHelper fileHelper;

	// Text file
	{
		std::string text;
		fileHelper.ReadTextFile("test_exist.txt",text);
		auto text2 = text + "\nWell that's another one";
		fileHelper.WriteTextFile("test_exist2.txt",text2);
	}

	// Binary file
	{
		struct cTemp{unsigned a; float b;double c;} temp,temp2;
		temp.a = 1;
		temp.b = 2.0f;
		temp.c = 3;

		fileHelper.WriteBinFile("test_exist.bin", cWrapBlob((void *)&temp, sizeof(temp)));

		cVecBlob blob;
		fileHelper.ReadBinFile("test_exist.bin",blob);

		temp2 = *(reinterpret_cast<const cTemp * const>(blob.Data()));
	}

}

void cTestApp::TestGPU()
{
	GLenum err;
	cShader<GL_VERTEX_SHADER> vs;
	cShader<GL_FRAGMENT_SHADER> ps;

	vs.LoadTextFile("shader.vert");
	ps.LoadTextFile("shader.frag");

	cProgram testShader;
	testShader.Attach(vs);
	testShader.Attach(ps);

	testShader.Link();
}