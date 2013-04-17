#pragma once

#include <string>

namespace gel
{

	template<class T>
	inline std::string ToString(const T& v)
	{
		std::ostringstream sstream;
		sstream << v;
		return sstream.str();
	}

	template<class T>
	inline T FromString(const std::string& v)
	{
		T res;
		std::istringstream sstream(v.c_str());
		sstream >> res;
		return res;
	}

	template<> inline std::string ToString<std::string>(const std::string& v) {return v;}
	template<> inline std::string FromString<std::string>(const std::string& v) {return v;}

	inline std::wstring AsciiToWide(const std::string& zText) { return std::wstring(zText.begin(), zText.end()); }
	inline std::string WideToAscii(const std::wstring& zText) { return std::string(zText.begin(), zText.end()); }
}