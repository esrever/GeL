#include "blob.h"

namespace gel
{

	cWrapBlob::cWrapBlob(const void * const zData, unsigned zLength)
		:mData(zData)
		,mLength(zLength)
	{
	}

	cVecBlob::cVecBlob(const void * const zData, unsigned zLength)
	{
		if(zData != nullptr)
		{
			mData.resize(zLength);
			memcpy(&mData.front(),zData,zLength);
		}
	}
}