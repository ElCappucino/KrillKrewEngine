#include "Joystick.h"

std::unordered_map<int, std::unique_ptr<Joystick::Controller>> Joystick::availableJoysticks;

void Joystick::OnJoystickConnected(SDL_ControllerDeviceEvent& e)
{
	int deviceIndex = e.which;

	if (SDL_IsGameController(deviceIndex))
	{
		SDL_GameController* controller = SDL_GameControllerOpen(deviceIndex);
		if (controller)
		{
			auto c = std::make_unique<Controller>();
			c->gc = controller;
			c->joystickIndex = deviceIndex;

			std::fill(c->buttons.begin(), c->buttons.end(), false);
			std::fill(c->lastButtons.begin(), c->lastButtons.end(), false);
			std::fill(c->axes.begin(), c->axes.end(), 0.f);
			std::fill(c->lastAxes.begin(), c->lastAxes.end(), 0.f);

			int mapIndex = GetNextFreeIndex();

			KK_INFO("Controller Connected: Mapindex: {0} DeviceIndex: {1}", mapIndex, deviceIndex);

			availableJoysticks[mapIndex] = std::move(c);
		}
		else
		{
			KK_ERROR("Error: Unable to open game controller with device index: {0}", deviceIndex);
		}
	}
	else
	{
		KK_ERROR("Device at index {0} is not recognized as a game controller", deviceIndex);
	}
}

void Joystick::OnJoystickDisconnected(SDL_ControllerDeviceEvent& e)
{
	int deviceIndex = e.which;
	for (auto it = availableJoysticks.begin(); it != availableJoysticks.end(); ++it)
	{
		Controller* c = it->second.get();
		if (c->joystickIndex == deviceIndex)
		{
			SDL_GameControllerClose(c->gc);
			availableJoysticks.erase(it);
			break;
		}
	}
}

void Joystick::Shutdown()
{
	for (auto it = availableJoysticks.begin(); it != availableJoysticks.end();)
	{
		Controller* c = it->second.get();
		SDL_GameControllerClose(c->gc);
		it = availableJoysticks.erase(it);
	}
}

void Joystick::Update()
{
	for (auto& pair : availableJoysticks)
	{
		Controller* c = pair.second.get();

		if (c && c->gc)
		{
			c->lastButtons = c->buttons;
			c->lastAxes = c->axes;

			for (int i = 0; i < static_cast<int>(Button::Count); i++)
			{
				c->buttons[i] = SDL_GameControllerGetButton(c->gc, static_cast<SDL_GameControllerButton>(i));
			}

			for (int i = 0; i < static_cast<int>(Axis::Count); i++)
			{
				Sint16 raw = SDL_GameControllerGetAxis(c->gc, static_cast<SDL_GameControllerAxis>(i));
				c->axes[i] = static_cast<float>(raw) / 32768.0f;
			}
		}
	}
}

bool Joystick::GetButton(int joystickId, Button button)
{
	auto it = availableJoysticks.find(joystickId);

	if (it != availableJoysticks.end())
	{
		return it->second->buttons[static_cast<int>(button)];
	}

	KK_ERROR("Joystick with id {0} is not available", joystickId);
	return false;
}

bool Joystick::GetButtonDown(int joystickId, Button button)
{
	auto it = availableJoysticks.find(joystickId);

	if (it != availableJoysticks.end())
	{
		bool down = it->second->buttons[static_cast<int>(button)] &&
			!it->second->lastButtons[static_cast<int>(button)];
		if (down)
			KK_CORE_INFO("GetButtonDown: joystickId = {0}, button = {1}", joystickId, static_cast<int>(button));
		return down;
	}

	return false;
}

bool Joystick::GetButtonUp(int joystickId, Button button)
{
	auto it = availableJoysticks.find(joystickId);

	if (it != availableJoysticks.end())
	{
		return !it->second->buttons[static_cast<int>(button)] &&
			it->second->lastButtons[static_cast<int>(button)];
	}

	return false;
}

float Joystick::GetAxis(int joystickId, Axis axis)
{
	auto it = availableJoysticks.find(joystickId);

	if (it != availableJoysticks.end())
	{
		KK_INFO("Joystick::GetAxis joystickId = {0} float = {1}", joystickId, it->second->axes[static_cast<int>(axis)]);
		return it->second->axes[static_cast<int>(axis)];
	}

	return 0.f;
}

int Joystick::GetNextFreeIndex()
{
	int ret = -1;

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (availableJoysticks.count(i) == 0)
		{
			ret = i;
			break;
		}
	}

	return ret;
}
