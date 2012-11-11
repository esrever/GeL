#pragma once

#include <glm/glm.hpp>
#include <string>

using namespace std;

namespace gel
{
	class cGlutWindow
	{
	public:
		struct cCreationParams
		{
			cCreationParams();
			int			mDisplayMode;
			glm::ivec2	mContextVersion;
			int			mContextFlags;
			int			mContextProfile;
			glm::ivec2	mWindowPosition;
			glm::ivec2	mWindowSize;
			string		mWindowTitle;
		};
		void Create(int argc, char ** argv, const cCreationParams& params = cCreationParams());
	};
}