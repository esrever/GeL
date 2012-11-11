#include "camera.h"

#include <glm/gtc/swizzle.hpp>
#include <cassert>

namespace gel
{
	//---------------------------------------------------------------------------------------------
	cCamera::cViewParams::cViewParams()
		:mEye(z_axis)
		,mCenter(0.0f,0.0f,0.0f)
		,mUp(y_axis)
	{
	}

	//---------------------------------------------------------------------------------------------
	cCamera::cProjParams::cProjParams()
		:mAspectRatio(1.0f)
		,mFoV(0.92f)
		,mNear(1e-03f)
		,mFar(1e02f)
	{
	}

	//---------------------------------------------------------------------------------------------
	cCamera::cCamera()
		:mMoveSpeed(1.0f)
		,mRotSpeed(1.0f)
	{
		SetView(mViewParams);
		SetProj(mProjParams);
	}

	//---------------------------------------------------------------------------------------------
	void cCamera::ExtractParams(const glm::mat4& zMat, cViewParams& zParams)
	{
		glm::vec4 view4 = glm::mul ( glm::vec4(0.0f, 0.0f, -1.0f, 1.0f), zMat);
		glm::vec4 eye4 = glm::mul ( glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), zMat);
		glm::vec4 up4 = glm::mul ( glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), zMat);

		glm::vec3 view = glm::vec3( view4.x, view4.y, view4.z);
		view /= view4.w;

		glm::vec3 eye = glm::vec3( eye4.x, eye4.y, eye4.z);
		eye /= eye4.w;
		
		glm::vec3 up = glm::vec3( up4.x, up4.y, up4.z);
		up /= up4.w;

		zParams.mUp = glm::vec3(zMat[1][0],zMat[1][1],zMat[1][2]);
		glm::mat4 matInv = glm::inverse(zMat);
		zParams.mEye = glm::vec3(matInv[3][0],matInv[3][1],matInv[3][2]);
		zParams.mCenter = zParams.mEye - glm::vec3(matInv[2][0],matInv[2][1],matInv[2][2]);
		
	}

	//---------------------------------------------------------------------------------------------
	void cCamera::ExtractParams(const glm::mat4& zMat, cProjParams& zParams)
	{
		float const aa = zMat[0][0];
		float const bb = zMat[1][1];
		float const cc = zMat[2][2];
		float const dd = zMat[3][2];

		zParams.mAspectRatio = bb / aa;
		zParams.mFoV     = 2.0f * atan(1.0f / bb);

		float const kk = (cc - 1.0f) / (cc + 1.0f);
		zParams.mNear = (dd * (1.0f - kk)) / (2.0f * kk);
		zParams.mFar = kk * zParams.mNear;
	}

	//---------------------------------------------------------------------------------------------
	void cCamera::Translate(float zX, float zY, float zZ)
	{

	}

	//---------------------------------------------------------------------------------------------
	void cCamera::Rotate(float zAngle, const glm::vec3& zAxis)
	{
		
	}
}