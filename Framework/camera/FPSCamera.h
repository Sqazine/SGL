#pragma once
#include <cstdint>
#include "Camera.h"
#include "SGL/SGL.h"
class FPSCamera:public Camera
{
public:
	FPSCamera(float fov,float aspect,float znear,float zfar);
	~FPSCamera();

	void ProcessInput(SDL_Event event, const uint8_t* keyboardState) override;
	void Update() override;
private:
	float m_Yaw, m_Pitch;
	float m_MoveSpeed, m_RotateSpeed, m_BoostSpeed;

	SGL::Vector3f m_Up;
	SGL::Vector3f m_Right;
	SGL::Vector3f m_Front;
};
