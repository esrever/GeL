#pragma once

#include <vector>

namespace gel
{
	// Binary blob. Used for loading binary file contents and more.
	class cBlob
	{
		public:
			cBlob(const void * const zData=nullptr, unsigned zLength=0){}
			virtual ~cBlob(){}
			
			virtual const void * const Data() const { return nullptr; }
			virtual unsigned Length() const			{ return 0; }

		private:
	};

	class cWrapBlob : public cBlob
	{
	public:

		cWrapBlob(const void * const zData=nullptr, unsigned zLength=0);			
		virtual const void * const Data() const		{ return mData; }
		virtual unsigned Length() const				{ return mLength; }

	private:
		const void * const mData;
		unsigned mLength;
	};

	class cVecBlob : public cBlob
	{
		public:
			cVecBlob(const void * const zData=nullptr, unsigned zLength=0);
			cVecBlob(const std::vector<char>& zData)	{ mData = zData; mLength = zData.size(); }

			virtual const void * const Data() const		{ return &mData.front(); }
			virtual unsigned Length() const				{ return mLength; }

		private:
			std::vector<char> mData;
			unsigned mLength;
	};
}