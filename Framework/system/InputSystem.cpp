#include "InputSystem.h"
#include <memory>

KeyboardState::KeyboardState()
{
}
KeyboardState::~KeyboardState()
{
}
bool KeyboardState::GetKeyValue(KeyCode keyCode) const
{
	return m_CurKeyState[keyCode] == 1 ? true : false;
}

BUTTON_STATE KeyboardState::GetKeyState(KeyCode keyCode) const
{
	if (m_PreKeyState[keyCode] == 0)
	{
		if (m_CurKeyState[keyCode] == 0)
			return BUTTON_STATE::NONE;
		else
			return BUTTON_STATE::PRESS;
	}
	else
	{
		if (m_CurKeyState[keyCode] == 0)
			return BUTTON_STATE::RELEASE;
		else
			return BUTTON_STATE::HOLD;
	}
}

MouseState::MouseState()
	: m_CurPos(SGL::Vector2i32(0.0f)), m_PrePos(SGL::Vector2i32(0.0f)), m_MouseScrollWheel(SGL::Vector2i32(0.0f)), m_CurButtons(0), m_PreButtons(0)
{
}
MouseState::~MouseState()
{
}
bool MouseState::GetButtonValue(int button) const
{
	return (m_CurButtons & SDL_BUTTON(button)) == 1;
}

BUTTON_STATE MouseState::GetButtonState(int button) const
{
	if ((m_PreButtons & SDL_BUTTON(button)) == 0)
	{
		if ((m_PreButtons & SDL_BUTTON(button)) == 0)
			return BUTTON_STATE::NONE;
		else
			return BUTTON_STATE::PRESS;
	}
	else
	{
		if ((m_PreButtons & SDL_BUTTON(button)) == 0)
			return BUTTON_STATE::RELEASE;
		else
			return BUTTON_STATE::HOLD;
	}
}

SGL::Vector2i32 MouseState::GetMousePos() const
{
	return m_CurPos;
}

SGL::Vector2i32 MouseState::GetReleativeMove() const
{
	return m_CurPos - m_PrePos;
}

SGL::Vector2i32 MouseState::GetMouseScrollWheel() const
{
	return m_MouseScrollWheel;
}

void MouseState::SetReleativeMode(bool isActive)
{
	m_IsRelative = isActive;
	if (isActive)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool MouseState::IsReleativeMode() const
{
	return m_IsRelative;
}

InputSystem::InputSystem()
	: m_KeyboardState(std::make_shared<KeyboardState>()), m_MouseState(std::make_shared<MouseState>())
{
	//获取SDL中键盘状态
	m_KeyboardState->m_CurKeyState = SDL_GetKeyboardState(nullptr);
	//清空前一帧键盘状态的值（游戏开始前没有状态）
	m_KeyboardState->m_PreKeyState = new uint8_t[SDL_NUM_SCANCODES];
	memset(m_KeyboardState->m_PreKeyState, 0, SDL_NUM_SCANCODES);
}

InputSystem::~InputSystem()
{
}

void InputSystem::PreUpdate()
{
	memcpy_s(m_KeyboardState->m_PreKeyState, SDL_NUM_SCANCODES, m_KeyboardState->m_CurKeyState, SDL_NUM_SCANCODES);
	m_MouseState->m_PreButtons = m_MouseState->m_CurButtons;
	m_MouseState->m_PrePos = m_MouseState->m_CurPos;
	m_MouseState->m_MouseScrollWheel = SGL::Vector2i32(0);
}

void InputSystem::PostUpdate()
{
	SGL::Vector2i32 p = SGL::Vector2i32(0);
	//更新当前帧的鼠标按键的状态
	if (!m_MouseState->m_IsRelative) //获取鼠标光标位置的绝对位置
		m_MouseState->m_CurButtons = SDL_GetMouseState(&p.x, &p.y);
	else //获取鼠标光标的相对位置
		m_MouseState->m_CurButtons = SDL_GetRelativeMouseState(&p.x, &p.y);
	//更新当前帧的鼠标光标位置
	m_MouseState->m_CurPos = p;
}

void InputSystem::ProcessInput(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_MOUSEWHEEL:
		m_InputEventType = SDL_MOUSEWHEEL;
		m_MouseState->m_MouseScrollWheel = SGL::Vector2i32(event.wheel.x, event.wheel.y);
		break;
	case SDL_MOUSEMOTION:
		m_InputEventType = SDL_MOUSEMOTION;
		break;
	case SDL_QUIT:
		m_InputEventType=SDL_QUIT;
		break;
	default:
		break;
	}
}

const std::shared_ptr<KeyboardState> &InputSystem::GetKeyboard() const
{
	return m_KeyboardState;
}

const std::shared_ptr<MouseState> &InputSystem::GetMouse() const
{
	return m_MouseState;
}

uint32_t InputSystem::GetEventType() const
{
	return m_InputEventType;
}