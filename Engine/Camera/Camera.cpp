#include "Camera.h"
Camera::Camera(float left, float right, float top, float bottom, float znear, float zfar)
	:m_Target(SGL::Vector3f::ZERO),m_Position(SGL::Vector3f(0.0f,0.0f,10.0f))
{
	m_ProjectionMatrix = SGL::Matrix4f::GLOrthoGraphic(left, right, top, bottom, znear, zfar);
	m_ViewMatrix = SGL::Matrix4f::LookAt(m_Position,m_Target,SGL::Vector3f::UNIT_Y);
}

Camera::Camera(float fov, float aspect, float znear, float zfar)
	:m_Target(SGL::Vector3f::ZERO)
{
	m_ProjectionMatrix = SGL::Matrix4f::GLPerspective(fov, aspect, znear, zfar);
	m_ViewMatrix = SGL::Matrix4f::LookAt(m_Position, m_Target, SGL::Vector3f::UNIT_Y);
}

Camera::~Camera()
{
}

void Camera::SetPosition(const SGL::Vector3f& pos)
{
	m_Position = pos;
}

const SGL::Vector3f& Camera::GetPosition() const
{

	return m_Position;
}

void Camera::SetTarget(const SGL::Vector3f& tar)
{
	m_Target = tar;
}

const SGL::Vector3f& Camera::GetTarget() const
{

	return m_Target;
}

const SGL::Matrix4f& Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

const SGL::Matrix4f& Camera::GetProjectionMatrix() const
{

	return m_ProjectionMatrix;
}
