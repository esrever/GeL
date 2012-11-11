#include "arccam.h"

namespace gel
{
	void cArcCam::Move(float zX, float zY, float zZ)
	{
		// First apply the fwd/back
		mViewParams.mEye += zZ*mViewParams.mViewDir;

		// Calc radius
		float R = glm::length(mViewParams.mEye - mCenter);

		// Calc the rotation axis: for Up movement is X: cross product of (Center-Eye) x Up
		glm::vec3 rotaxis_up = glm::normalize(glm::cross( glm::normalize(mCenter - mViewParams.mEye), mViewParams.mUp));

		// center our system
		mViewParams.mEye -= mCenter;
	
		// Apply the Y rotation
		float angleUp = 180 * zY / R;
		mViewParams.mEye = glm::rotate(mViewParams.mEye,angleUp,rotaxis_up);

		// Apply the X rotation
		glm::vec3 right = glm::normalize(glm::cross(mViewParams.mViewDir, mViewParams.mUp));
		glm::vec3 rotaxis_right = glm::normalize(glm::cross( glm::normalize(mCenter - mViewParams.mEye), right));
		float angleRight = 180 * zX / R;
		mViewParams.mEye = glm::rotate(mViewParams.mEye,angleRight,rotaxis_right);

		// Recalculate
		mViewParams.mEye = mCenter;

		SetView(mViewParams);
	}

	void cArcCam::Rotate(float zAngle, const glm::vec3& zAxis)
	{

	}
}