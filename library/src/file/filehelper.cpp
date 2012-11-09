#include "filehelper.h"

#include <cassert>
#include <windows.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <pystring/pystring.h>

namespace gel {

	//----------------------------------------------------------------------------------
	bool cFileHelper::FileExists(const std::string& zFilename) const
	{
		DWORD fileAttr = GetFileAttributesA(zFilename.c_str());
		return !((fileAttr == 0xFFFFFFFF) || (fileAttr == FILE_ATTRIBUTE_DIRECTORY));
	}

	//----------------------------------------------------------------------------------
	bool cFileHelper::IsBareName(const std::string& zFilename) const
	{
		int i = std::max(pystring::find(zFilename,"/"),
						 pystring::find(zFilename,"\\"));
		return i == -1;
	}
	
	//----------------------------------------------------------------------------------
	const std::string cFileHelper::FileExistsInList(const std::string& zFilename,
	    							   const std::string& zListname) const
	{
		assert(IsBareName(zFilename));
		auto dirlist = mDirectoryLists.find(zListname);
		if (dirlist != mDirectoryLists.end() )
		{
			for( auto dir : dirlist->second)
			{
				std::string fullpath = pystring::os::path::join(dir, zFilename);
				if(FileExists(fullpath))
					return fullpath;
			}
		}
		return "";
	}

	//----------------------------------------------------------------------------------
	const std::string cFileHelper::FindFile(const std::string& zFileName) const
	{
		if(!IsBareName(zFileName))
		{
			return FileExists(zFileName) ? zFileName : "";
		}
		else
		{
			for( auto list : mDirectoryLists)
			{
				std::string fullpath = FileExistsInList(zFileName, list.first);
				if (fullpath != "")
					return fullpath;
			}
			return "";
		}
	}


	//----------------------------------------------------------------------------------
	bool cFileHelper::ReadTextFile(const std::string& zFilename, std::string& zText)
	{
		std::string fname = FindFile(zFilename);
		std::ifstream t(fname);
		if( t.good())
		{
			t.seekg(0, std::ios::end);   
			zText.reserve(unsigned(t.tellg()));
			t.seekg(0, std::ios::beg);

			zText.assign((std::istreambuf_iterator<char>(t)),
						std::istreambuf_iterator<char>());
			return true;
		}
		else
			return false;
	}
	
	//----------------------------------------------------------------------------------
	bool cFileHelper::ReadBinFile(const std::string& zFilename, cBlob& zBlob)
	{
		std::string fname = FindFile(zFilename);
		if( fname != "")
		{
			
			return true;
		}
		else
			return false;
	}
	
	//----------------------------------------------------------------------------------
	bool cFileHelper::WriteTextFile(const std::string& zFilename, const std::string& zText)
	{
		std::string fname = FindFile(zFilename);
		if( fname != "")
		{
			
			return true;
		}
		else
			return false;
	}
	
	//----------------------------------------------------------------------------------
	bool cFileHelper::WriteBinFile(const std::string& zFilename, const cBlob& zBlob)
	{
		std::string fname = FindFile(zFilename);
		if( fname != "")
		{
			
			return true;
		}
		else
			return false;
	}
}