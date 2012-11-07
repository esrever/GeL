#include "filehelper.h"

#include <cassert>
#include <windows.h>
#include <pystring/pystring.h>

namespace gel {

	bool cFileHelper::FileExists(const std::string& zFilename) const
	{
		DWORD fileAttr = GetFileAttributesA(zFilename.c_str());
		return !((fileAttr == 0xFFFFFFFF) || (fileAttr == FILE_ATTRIBUTE_DIRECTORY));
	}

	bool cFileHelper::IsBareName(const std::string& zFilename) const
	{
		int i = std::max(pystring::find(zFilename,"/"),
						 pystring::find(zFilename,"\\"));
		return i == -1;
	}
	
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

}