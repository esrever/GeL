#pragma once

namespace gel
{
	// Binary blob. Used for loading binary file contents and more.
	class cBlob
	{
		public:
			cBlob(const void * const zData, unsigned zLength)
				:mData(zData),mLength(zLength){}

			const void * const Data() const { return mData; }
			unsigned Length() const			{ return mLength; }

		private:
			const void * const mData;
			unsigned mLength;
	};
}