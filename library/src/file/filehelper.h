#pragma once

#include <map>
#include <vector>
#include <string>

/*
	I  need an fstream helper, not substitute
		Open file: 
			if given barename, look/try many locations
				cFileHelper::Lists["Textures"]
				cFileHelper::Lists["Models"]
				etc
		Read whole text file
		Read text line
		Read whole binary file
		File exists
		File in list exists
*/
namespace gel {
class cFileHelper
{  
public:
	typedef std::vector<std::string> dirlist_type;
	typedef std::map< std::string, dirlist_type> dirlist_map_type;

	// Does the file exist?
	bool FileExists(const std::string& zFilename) const;

	// Is the filename bare?
	bool IsBareName(const std::string& zFilename) const;

	// Look for the file in a specified list. File must not be bare name
	const std::string FileExistsInList(const std::string& zFilename,
	    							   const std::string& zListname) const;

	// Look through all the lists to find the file
	const std::string FindFile(const std::string& zFilename) const;
	
	dirlist_map_type mDirectoryLists;
};

}