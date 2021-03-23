#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <memory>

enum class BUTTON_STATE
{
	NONE,
	PRESS,
	RELEASE,
	HOLD
};

class KeyboardState
{
public:
	KeyboardState();
	~KeyboardState();
	bool GetKeyValue(SDL_Scancode keyCode) const;
	enum BUTTON_STATE GetKeyState(SDL_Scancode keyCode) const;

private:
	friend class InputSystem;
	const uint8_t *m_CurKeyState;
	uint8_t *m_PreKeyState;
};

class MouseState
{
public:
	MouseState();
	~MouseState();
	bool GetButtonValue(int button) const;
	enum BUTTON_STATE GetButtonState(int button) const;
	glm::vec2 GetMousePos() const;
	glm::vec2 GetReleativeMove() const;
	glm::vec2 GetMouseScrollWheel() const;

	void SetReleativeMode(bool isActive);
	bool IsReleativeMode() const;

private:
	friend class InputSystem;
	bool m_IsRelative;
	glm::ivec2 m_CurPos;
	glm::ivec2 m_PrePos;
	glm::ivec2 m_MouseScrollWheel;
	uint32_t m_CurButtons;
	uint32_t m_PreButtons;
};

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	void PreUpdate();
	void PostUpdate();
	void ProcessInput(SDL_Event event);
	const std::shared_ptr<KeyboardState> &GetKeyboard() const;
	const std::shared_ptr<MouseState> &GetMouse() const;

	uint32_t GetEventType() const;

private:
	uint32_t m_InputEventType;
	std::shared_ptr<KeyboardState> m_KeyboardState;
	std::shared_ptr<MouseState> m_MouseState;
};