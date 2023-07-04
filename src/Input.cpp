#include "Input.h"

#include <SDL.h>

InputInteraction Input::LastInput = InputInteraction{ InputType::NONE, WindowEventType::NONE, KeyboardEventType::NONE };

bool Input::TimerEnd = false;

Uint32  endTimer(Uint32 interval, void* param)
{
	Input::TimerEnd = true;

	return 0;
}

void Input::getInput()
{
	Input::TimerEnd = false;

	//SDL_TimerID Timer = SDL_AddTimer(2000, endTimer, nullptr);

	while (Input::LastInput.Type == InputType::NONE || Input::TimerEnd == false)
	{
		SDL_Event Event;

		while (SDL_WaitEvent(&Event))
		{
			switch (Event.type)
			{
			case SDL_KEYDOWN:
				if (Event.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					Input::LastInput = { InputType::KEYBOARD_EVENT, WindowEventType::NONE, KeyboardEventType::DOWN };
					return;
				}

				else if (Event.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					Input::LastInput = { InputType::KEYBOARD_EVENT, WindowEventType::NONE, KeyboardEventType::UP };
					return;
				}

				else if (Event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					Input::LastInput = { InputType::KEYBOARD_EVENT, WindowEventType::NONE, KeyboardEventType::LEFT };
					return;
				}

				else if (Event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					Input::LastInput = { InputType::KEYBOARD_EVENT, WindowEventType::NONE, KeyboardEventType::RIGHT };
					return;
				}

				break;

			case SDL_QUIT:
				Input::LastInput = { InputType::WINDOW_EVENT, WindowEventType::WINDOW_CLOSED, KeyboardEventType::NONE };
				return;

			case SDL_WINDOWEVENT:
				if (Event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Input::LastInput = { InputType::WINDOW_EVENT, WindowEventType::WINDOW_RESIZE, KeyboardEventType::NONE };
					return;
				}
				break;

			default:
				break;
			}
		}
	}

	//SDL_RemoveTimer(Timer);
}
