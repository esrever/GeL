#include "fileutils.h"

#include <windows.h>

namespace gel
{
	std::vector<std::string> OpenFileDialog(const char * filter)
	{
		char curDir[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH,curDir);
		std::vector<char> filedata(MAX_PATH * 1000);
		char * szFileName = &filedata[0];
		OPENFILENAMEA opf;
		opf.hwndOwner = 0;
		opf.lpstrFilter = filter;
		opf.lpstrCustomFilter = 0;
		opf.nMaxCustFilter = 0L;
		opf.nFilterIndex = 1L;
		opf.lpstrFile = szFileName;
		opf.nMaxFile = (DWORD)filedata.size();
		opf.lpstrFileTitle = 0;
		opf.nMaxFileTitle=50;
		opf.lpstrInitialDir = 0;
		opf.lpstrTitle = "Open";
		opf.nFileOffset = 0;
		opf.nFileExtension = 2;
		opf.lpstrDefExt = "*.*";
		opf.lpfnHook = NULL;
		opf.lCustData = 0;
		opf.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
		//opf.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
		opf.lStructSize = sizeof(OPENFILENAMEA);
		std::vector<std::string> retval;
		if(GetOpenFileNameA(&opf))
		{
			if(opf.nFileOffset > strlen(szFileName))
			{
				std::string path = std::string(szFileName) + "\\";
				unsigned startOffset = opf.nFileOffset;
				while(szFileName[startOffset])
				{
					retval.push_back( path + std::string(&szFileName[startOffset]));
					startOffset += (unsigned int) strlen(&szFileName[startOffset])+1;
				}
			}
			else
				retval.push_back(szFileName);
		}
		else
		{
			DWORD retval = CommDlgExtendedError();
			while(0);
		}
		SetCurrentDirectoryA(curDir);
		return retval;
	}
}