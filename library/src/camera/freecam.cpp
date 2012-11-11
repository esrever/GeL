#include "freecam.h"

namespace gel
{
	void cFreeCam::Move(float zX, float zY, float zZ)
	{
		mViewParams.mEye += zZ*mViewParams.mViewDir;
		mViewParams.mEye += zY*mViewParams.mUp;

		glm::vec3 right = glm::normalize(glm::cross(mViewParams.mViewDir, mViewParams.mUp));
		mViewParams.mEye += zX*right;

		SetView(mViewParams);
	}

	void cFreeCam::Rotate(float zAngle, const glm::vec3& zAxis)
	{
		float angleDeg = glm::degrees(zAngle);
		mViewParams.mViewDir = glm::rotate(mViewParams.mViewDir,angleDeg,zAxis);
		mViewParams.mUp = glm::rotate(mViewParams.mUp,angleDeg,zAxis);
		SetView(mViewParams);
	}
}