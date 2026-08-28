#include "InputSystem.h"
#include <memory>

bool InputSystem::GetKeyValue(KeyCode keyCode) const
{
	return m_CurKeyState[keyCode] == 1 ? true : false;
}

BUTTON_STATE InputSystem::GetKeyState(KeyCode keyCode) const
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

bool InputSystem::GetMouseButtonValue(int button) const
{
	return (m_CurMouseButtons & SDL_BUTTON(button)) == 1;
}

BUTTON_STATE InputSystem::GetMouseButtonState(int button) const
{
	if ((m_PreMouseButtons & SDL_BUTTON(button)) == 0)
	{
		if ((m_PreMouseButtons & SDL_BUTTON(button)) == 0)
			return BUTTON_STATE::NONE;
		else
			return BUTTON_STATE::PRESS;
	}
	else
	{
		if ((m_PreMouseButtons & SDL_BUTTON(button)) == 0)
			return BUTTON_STATE::RELEASE;
		else
			return BUTTON_STATE::HOLD;
	}
}

SGL::Vector2i32 InputSystem::GetMousePos() const
{
	return m_CurMousePos;
}

SGL::Vector2i32 InputSystem::GetMouseRelativeMove() const
{
	return m_CurMousePos - m_PreMousePos;
}

SGL::Vector2i32 InputSystem::GetMouseScrollWheel() const
{
	return m_MouseScrollWheel;
}

void InputSystem::SetMouseRelativeMode(bool isActive)
{
	m_IsMouseRelative = isActive;
	if (isActive)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool InputSystem::IsMouseRelativeMode() const
{
	return m_IsMouseRelative;
}

InputSystem::InputSystem()
{
	//获取SDL中键盘状态
	m_CurKeyState = SDL_GetKeyboardState(nullptr);
	//清空前一帧键盘状态的值（游戏开始前没有状态）
	m_PreKeyState = new uint8_t[SDL_NUM_SCANCODES];
	memset(m_PreKeyState, 0, SDL_NUM_SCANCODES);
}

InputSystem::~InputSystem()
{
}

void InputSystem::PreUpdate()
{
	memcpy_s(m_PreKeyState, SDL_NUM_SCANCODES, m_CurKeyState, SDL_NUM_SCANCODES);
	m_PreMouseButtons = m_CurMouseButtons;
	m_PreMousePos = m_CurMousePos;
	m_MouseScrollWheel = SGL::Vector2i32(0);
}

void InputSystem::PostUpdate()
{
	SGL::Vector2i32 p = SGL::Vector2i32(0);
	//更新当前帧的鼠标按键的状态
	if (!m_IsMouseRelative) //获取鼠标光标位置的绝对位置
		m_CurMouseButtons = SDL_GetMouseState(&p.x, &p.y);
	else //获取鼠标光标的相对位置
		m_CurMouseButtons = SDL_GetRelativeMouseState(&p.x, &p.y);
	//更新当前帧的鼠标光标位置
	m_CurMousePos = p;
}

void InputSystem::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEWHEEL:
			m_InputEventType = (EventType)SDL_MOUSEWHEEL;
			m_MouseScrollWheel = SGL::Vector2i32(event.wheel.x, event.wheel.y);
			break;
		case SDL_MOUSEMOTION:
			m_InputEventType = (EventType)SDL_MOUSEMOTION;
			break;
		case SDL_QUIT:
			m_InputEventType = (EventType)SDL_QUIT;
			break;
		default:
			break;
		}
	}
}

EventType InputSystem::GetEventType() const
{
	return m_InputEventType;
}