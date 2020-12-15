#pragma once
#include <cstdint>
#include "Camera.h"
#include "../libSGL/libSGL.h"
class FPSCamera:public Camera
{
public:
	FPSCamera(float fov,float aspect,float znear,float zfar);
	~FPSCamera();

	void ProcessInput(SDL_Event event, const uint8_t* keyboardState) override;
	void Update() override;
private:
	float m_Yaw, m_Pitch, m_Roll;
	float m_MoveSpeed, m_RotateSpeed, m_BoostSpeed;

	SGLVector3f m_Up;
	SGLVector3f m_Right;
	SGLVector3f m_Front;
};

