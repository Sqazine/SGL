#pragma once
#include "SGL/SGL.h"
#include <SDL2/SDL.h>
class Camera
{
public:
	Camera(float left,float right,float top,float bottom,float znear,float zfar);
	Camera(float fov, float aspect, float znear, float zfar);
	~Camera();

	virtual void ProcessInput(SDL_Event event, const uint8_t* keyboardState) {}
	virtual void Update() {}

	void SetPosition(const SGL::Vector3f& pos);
	const SGL::Vector3f& GetPosition() const;

	void SetTarget(const SGL::Vector3f& tar);
	const SGL::Vector3f& GetTarget() const;

	const SGL::Matrix4f& GetViewMatrix() const;
	const SGL::Matrix4f& GetProjectionMatrix() const;
protected:			
	SGL::Matrix4f m_ViewMatrix;
	SGL::Matrix4f m_ProjectionMatrix;
	SGL::Vector3f m_Position;
	SGL::Vector3f m_Target;

};

