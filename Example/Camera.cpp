#include "Camera.h"
#include "SGL.h"
Camera::Camera(float left, float right, float top, float bottom, float znear, float zfar)
	:m_Target(SGLVector3f::ZERO),m_Position(SGLVector3f(0.0f,0.0f,10.0f))
{
	m_ProjectionMatrix = SGLMatrix4f::GLOrthoGraphic(left, right, top, bottom, znear, zfar);
	m_ViewMatrix = SGLMatrix4f::LookAt(m_Position,m_Target,SGLVector3f::UNIT_Y);
}

Camera::Camera(float fov, float aspect, float znear, float zfar)
	:m_Target(SGLVector3f::ZERO)
{
	m_ProjectionMatrix = SGLMatrix4f::GLPerspective(fov, aspect, znear, zfar);
	m_ViewMatrix = SGLMatrix4f::LookAt(m_Position, m_Target, SGLVector3f::UNIT_Y);
}

Camera::~Camera()
{
}

void Camera::SetPosition(const SGLVector3f& pos)
{
	m_Position = pos;
}

const SGLVector3f& Camera::GetPosition() const
{

	return m_Position;
}

void Camera::SetTarget(const SGLVector3f& tar)
{
	m_Target = tar;
}

const SGLVector3f& Camera::GetTarget() const
{

	return m_Target;
}

const SGLMatrix4f& Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

const SGLMatrix4f& Camera::GetProjectionMatrix() const
{

	return m_ProjectionMatrix;
}
