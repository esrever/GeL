#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace gel
{
	static const glm::vec3 x_axis(1.0f,0.0f,0.0f);
	static const glm::vec3 y_axis(0.0f,1.0f,0.0f);
	static const glm::vec3 z_axis(0.0f,0.0f,1.0f);

	class cCamera
	{
	public:

		// Struct definitions
		// TODO: proj here is a specific perspective proj. I might need to expand that
		struct cProjParams
		{
			cProjParams();
			float mAspectRatio;
			float mFoV;
			float mNear;
			float mFar;
		};

		struct cViewParams
		{
			cViewParams();
			glm::vec3 mEye;
			glm::vec3 mViewDir;
			glm::vec3 mUp;
		};


		// ctor/dtor
		// TODO: I want two cams: free cam and obj cam (arcball?)
		cCamera();
		virtual ~cCamera(){}
		
		// Mutators
		void SetWorld(const glm::mat4& zWorld)		{ mWorld = zWorld; }
		void SetView(const glm::mat4& zView)		{ mView = zView; ExtractParams(zView,mViewParams); }
		void SetProj(const glm::mat4& zProj) 		{ mProj = zProj; ExtractParams(zProj,mProjParams); }

		void SetView(const cViewParams& zParams)	{ mViewParams = zParams; mView = glm::lookAt(zParams.mEye, zParams.mEye + zParams.mViewDir, zParams.mUp);}
		void SetProj(const cProjParams& zParams)	{ mProjParams = zParams; mProj = glm::perspective(glm::degrees(zParams.mFoV), zParams.mAspectRatio, zParams.mNear, zParams.mFar);}
		
		// Accessors
		const cViewParams& ViewParams() const		{ return mViewParams;}
		const cProjParams& ProjParams() const		{ return mProjParams;}

		const glm::mat4& World() const				{ return mWorld; }
		const glm::mat4& View() const				{ return mView; }
		const glm::mat4& Proj() const				{ return mProj; }

		// TODO: send uniform block to passed shader (M,V,P,MV,VP,MVP, eye, view, up)

		// Frame-to-frame manipulation
		void SetSpeed(float zMoveSpeed, float zRotSpeed)		 { mMoveSpeed = zMoveSpeed; mRotSpeed = zRotSpeed;}
		void GetSpeed(float& zMoveSpeed, float& zRotSpeed) const { zMoveSpeed = mMoveSpeed; zRotSpeed = mRotSpeed;}

		virtual void Move(float zX, float zY, float zZ) {}
		virtual void Rotate(float zAngle, const glm::vec3& zAxis){}

	public:

		// Common general ops
		static void ExtractParams(const glm::mat4& zMat, cViewParams& zParams);
		static void ExtractParams(const glm::mat4& zMat, cProjParams& zParams);

	protected:

		// matrices
		glm::mat4 mWorld;
		glm::mat4 mView;
		glm::mat4 mProj;

		// more data for each
		cProjParams mProjParams;
		cViewParams mViewParams;

		// speed
		float mMoveSpeed;
		float mRotSpeed;
	};
}