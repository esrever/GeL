#pragma once

#include <map>
#include <vector>
#include <string>

#include <core/blob.h>

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


	/// File queries
	// Does the file exist?
	bool FileExists(const std::string& zFilename) const;

	// Is the filename bare?
	bool IsBareName(const std::string& zFilename) const;

	// Look for the file in a specified list. File must not be bare name. Returns fullpath, else empty
	const std::string FileExistsInList(const std::string& zFilename,
	    							   const std::string& zListname) const;

	// Look through all the lists to find the file. Returns fullpath, else empty
	const std::string FindFile(const std::string& zFilename) const;


	/// File handling
	bool ReadTextFile(const std::string& zFilename, std::string& zText);
	bool ReadBinFile(const std::string& zFilename, cVecBlob& zBlob);
	bool WriteTextFile(const std::string& zFilename, const std::string& zText);
	bool WriteBinFile(const std::string& zFilename, const cBlob& zBlob);
	
	dirlist_map_type mDirectoryLists;
};

}