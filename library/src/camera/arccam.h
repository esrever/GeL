#pragma once

#include "camera.h"

namespace gel
{
	/*
		A camera that has the following semantics:
			- given a center C and a cam position:
				- move fwd/back: scalar
				- move lef/right, up/down: along the defined sphere
				- rotate, axis is vec towards center
	*/
	class cArcCam : public cCamera
	{
	public:
		virtual void Move(float zX, float zY, float zZ);
		virtual void Rotate(float zAngle, const glm::vec3& zAxis=glm::vec3());
		
		void SetCenter(const glm::vec3& zCenter) { mCenter = zCenter; }
		const glm::vec3& Center() const			 { return mCenter; }
	private:

		glm::vec3 mCenter;
	};
}