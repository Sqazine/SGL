#include "FPSCamera.h"
#include "utilities/Timer.h"
FPSCamera::FPSCamera(float fov, float aspect, float znear, float zfar)
	:Camera(fov, aspect, znear, zfar), m_MoveSpeed(10.0f), m_RotateSpeed(5.0f), m_BoostSpeed(10.0f),
	m_Yaw(SGLMath::ToRadian(-90.0f)), m_Pitch(0.0f), m_Roll(0.0f),m_Front(SGLVector3f(0.0f,0.0f,-1.0f)),m_Up(SGLVector3f::UNIT_Y),m_Right(SGLVector3f::UNIT_X)
{
}

FPSCamera::~FPSCamera()
{
}

void FPSCamera::ProcessInput(SDL_Event event, const uint8_t* keyboardState)
{
	float speed = 0.0f;
	if (keyboardState[SDL_SCANCODE_LSHIFT])
		speed = (m_MoveSpeed + m_BoostSpeed) * Timer::deltaTime;
	else speed = m_MoveSpeed * Timer::deltaTime;

	if (keyboardState[SDL_SCANCODE_W])
		m_Position += m_Front * speed;
	if (keyboardState[SDL_SCANCODE_S])
		m_Position -= m_Front * speed;
	if (keyboardState[SDL_SCANCODE_A])
		m_Position -= m_Right * speed;
	if (keyboardState[SDL_SCANCODE_D])
		m_Position += m_Right * speed;
	if (keyboardState[SDL_SCANCODE_E])
		m_Position += m_Up * speed;
	if (keyboardState[SDL_SCANCODE_Q])
		m_Position -= m_Up * speed;

	if (event.type == SDL_MOUSEMOTION)
	{
		int32_t mouseX, mouseY;

		SDL_GetRelativeMouseState(&mouseX, &mouseY);

		m_Yaw += SGLMath::ToRadian(mouseX * m_RotateSpeed * Timer::deltaTime);
		m_Pitch -= SGLMath::ToRadian(mouseY * m_RotateSpeed * Timer::deltaTime);

		//���ǲ�ϣ������ڸ���ʱ�����Ӿ���ת�����,���Ҫ���Ƹ�����
		m_Pitch = SGLMath::Clamp(m_Pitch, -89.0f, 89.0f);

		m_Front = SGLVector3f::Normalize(SGLVector3f(SGLMath::Cos(m_Pitch) * SGLMath::Cos(m_Yaw), SGLMath::Sin(m_Pitch), SGLMath::Cos(m_Pitch) * SGLMath::Sin(m_Yaw)));
		m_Right = SGLVector3f::Normalize(SGLVector3f::Cross(m_Front, SGLVector3f(0.0f, 1.0f, 0.0f)));
		m_Up = SGLVector3f::Normalize(SGLVector3f::Cross(m_Right, m_Front));
	}
	m_Target = m_Position + m_Front;
}

void FPSCamera::Update()
{
	m_ViewMatrix = SGLMatrix4f::LookAt(m_Position, m_Target, m_Up);
}
