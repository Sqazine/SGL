#pragma once
#include "../libSGL/libSGL.h"
#include <SDL2/SDL.h>
class Camera
{
public:
	Camera(float left,float right,float top,float bottom,float znear,float zfar);
	Camera(float fov, float aspect, float znear, float zfar);
	~Camera();

	virtual void ProcessInput(SDL_Event event, const uint8_t* keyboardState) {}
	virtual void Update() {}

	void SetPosition(const SGLVector3f& pos);
	const SGLVector3f& GetPosition() const;

	void SetTarget(const SGLVector3f& tar);
	const SGLVector3f& GetTarget() const;

	const SGLMatrix4f& GetViewMatrix() const;
	const SGLMatrix4f& GetProjectionMatrix() const;
protected:			
	SGLMatrix4f m_ViewMatrix;
	SGLMatrix4f m_ProjectionMatrix;
	SGLVector3f m_Position;
	SGLVector3f m_Target;

};

