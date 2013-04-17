#pragma once

/*
	Power-of-two utilities
*/

typedef unsigned int uint;

namespace gel
{
	namespace pot
	{
		inline uint NearestPowDown(uint v)
		{
			uint r=0;
			while(v>>=1)
				r++;
			return r;
		}

		inline uint NearestPowUp(uint v)
		{
			return NearestPowDown(v)+1;
		}

		inline uint NearestDown(uint v)
		{
			return 1<<NearestPowDown(v);
		}

		inline uint NearestUp(uint v)
		{
			return 1<<NearestPowUp(v);
		}
	}
}