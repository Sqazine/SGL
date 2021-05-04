#pragma once
#include <cstdint>
#include "Camera.h"
#include "SGL/SGL.h"
class FPCamera:public Camera
{
public:
	FPCamera(float fov,float aspect,float znear,float zfar);
	~FPCamera();

	void ProcessInput(const std::shared_ptr<InputSystem> &inputSystem) override;
	void Update() override;
private:
	float m_Yaw, m_Pitch;
	float m_MoveSpeed, m_RotateSpeed, m_BoostSpeed;

	SGL::Vector3f m_Up;
	SGL::Vector3f m_Right;
	SGL::Vector3f m_Front;
};

