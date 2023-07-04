#pragma once

enum class InputType
{
	NONE,
	WINDOW_EVENT,
	KEYBOARD_EVENT
};

enum class WindowEventType
{
	NONE,
	WINDOW_RESIZE,
	WINDOW_CLOSED
};

enum class KeyboardEventType
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct InputInteraction
{
	InputType Type;

	WindowEventType WindowType;

	KeyboardEventType KeyboardType;
};

class Input
{
public:

	static void getInput();

	static bool TimerEnd;

	static InputInteraction LastInput;

};

