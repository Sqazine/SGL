#include "FPCamera.h"
#include "utilities/Timer.h"
#include "system/InputSystem.h"
FPCamera::FPCamera(float fov, float aspect, float znear, float zfar)
	:Camera(fov, aspect, znear, zfar), m_MoveSpeed(10.0f), m_RotateSpeed(5.0f), m_BoostSpeed(10.0f),
	m_Yaw(SGL::Math::ToRadian(-90.0f)), m_Pitch(0.0f),m_Front(SGL::Vector3f(0.0f,0.0f,-1.0f)),m_Up(SGL::Vector3f::UNIT_Y),m_Right(SGL::Vector3f::UNIT_X)
{
}

FPCamera::~FPCamera()
{
}

void FPCamera::ProcessInput(const std::shared_ptr<InputSystem> &inputSystem)
{
	float speed = 0;
	if (inputSystem->GetKeyboard()->GetKeyState(KEYCODE_LSHIFT) == BUTTON_STATE::HOLD)
		speed = (m_MoveSpeed + m_BoostSpeed) * Timer::deltaTime;
	else
		speed = m_MoveSpeed * Timer::deltaTime;

	if (inputSystem->GetKeyboard()->GetKeyState(KEYCODE_W) == BUTTON_STATE::HOLD)
		m_Position += m_Front * speed;
	if (inputSystem->GetKeyboard()->GetKeyState(KEYCODE_S) == BUTTON_STATE::HOLD)
		m_Position -= m_Front * speed;
	if (inputSystem->GetKeyboard()->GetKeyState(KEYCODE_A) == BUTTON_STATE::HOLD)
		m_Position -= m_Right * speed;
	if (inputSystem->GetKeyboard()->GetKeyState(KEYCODE_D) == BUTTON_STATE::HOLD)
		m_Position += m_Right * speed;
	if (inputSystem->GetKeyboard()->GetKeyState(KEYCODE_E) == BUTTON_STATE::HOLD)
		m_Position += m_Up * speed;
	if (inputSystem->GetKeyboard()->GetKeyState(KEYCODE_Q) == BUTTON_STATE::HOLD)
		m_Position -= m_Up * speed;

	m_Yaw += inputSystem->GetMouse()->GetMousePos().x * m_RotateSpeed * Timer::deltaTime;
	m_Pitch -= inputSystem->GetMouse()->GetMousePos().y * m_RotateSpeed * Timer::deltaTime;

	//我们不希望相机在俯仰时发生视觉倒转的情况,因此要限制俯仰角
	m_Pitch = SGL::Math::Clamp(m_Pitch, -89.0f, 89.0f);

	m_Front = SGL::Vector3f::Normalize(SGL::Vector3f(SGL::Math::Cos(SGL::Math::ToRadian (m_Pitch)) * SGL::Math::Cos(SGL::Math::ToRadian (m_Yaw)), SGL::Math::Sin(SGL::Math::ToRadian (m_Pitch)), SGL::Math::Cos(SGL::Math::ToRadian (m_Pitch)) * SGL::Math::Sin(SGL::Math::ToRadian (m_Yaw))));
	m_Right = SGL::Vector3f::Normalize(SGL::Vector3f::Cross(m_Front, SGL::Vector3f::UNIT_Y));
	m_Up = SGL::Vector3f::Normalize(SGL::Vector3f::Cross(m_Right, m_Front));

	m_Target = m_Position + m_Front;
}

void FPCamera::Update()
{
	m_ViewMatrix = SGL::Matrix4f::LookAt(m_Position, m_Target, m_Up);
}
