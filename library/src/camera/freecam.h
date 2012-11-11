#pragma once

#include "camera.h"

namespace gel
{
	/*
		A free camera can move and rotate in 3-space, relatively to its current position
	*/
	class cFreeCam : public cCamera
	{
	public:
		virtual void Move(float zX, float zY, float zZ);
		virtual void Rotate(float zAngle, const glm::vec3& zAxis);
	private:
	};
}