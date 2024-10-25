#include "Joystick.h"

#include <algorithm>
#include <iostream>

#include "SDL_events.h"
#include "SDL_gamecontroller.h"

std::unordered_map<int, std::unique_ptr<Joystick::Controller>> Joystick::availableJoysticks;

void Joystick::OnJoystickConnected(SDL_ControllerDeviceEvent& e) 
{
	int deviceIndex = e.which;
	if (SDL_JoystickOpen(deviceIndex) != NULL) 
	{
		auto c = std::make_unique<Controller>();
		c->gc = SDL_JoystickOpen(deviceIndex);
		if (c->gc)
		{
			c->joystickIndex = deviceIndex;

			std::fill(c->buttons.begin(),		c->buttons.end(),		false);
			std::fill(c->lastButtons.begin(),	c->lastButtons.end(),	false);
			std::fill(c->axes.begin(),			c->axes.end(),			0.f);
			std::fill(c->lastAxes.begin(),		c->lastAxes.end(),		0.f);

			int mapIndex = GetNextFreeIndex();

			std::cout << "Joystick Connected: Mapindex: " << mapIndex << " DeviceIndex: " << deviceIndex << std::endl;

			availableJoysticks[mapIndex] = std::move(c);
		}
		else {
			std::cout << "Error: Unable to Connect joystick with the Device index : " << deviceIndex << std::endl;
		}
	}
}
void Joystick::OnJoystickDisconnected(SDL_ControllerDeviceEvent& e)
{
	int deviceIndex = e.which;
	for (auto it = availableJoysticks.begin(); it != availableJoysticks.end(); it++) 
	{
		Controller* c = it->second.get();
		if (c->joystickIndex == deviceIndex)
		{
			SDL_JoystickClose(c->gc);
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
		SDL_JoystickClose(c->gc);
		availableJoysticks.erase(it);
	}
}
void Joystick::Update()
{
	for (auto it = availableJoysticks.begin(); it != availableJoysticks.end(); it++)
	{
		Controller* c = it->second.get();
		if (c && c->gc) 
		{
			c->lastButtons = c->buttons;
			c->lastAxes = c->axes;

			for (unsigned int i = 0; i < static_cast<int>(Button::Count); i++) 
			{
				c->buttons[i] = SDL_JoystickGetButton(c->gc, i);
			}

			for (unsigned int i = 0; i < static_cast<int>(Axis::Count); i++) 
			{
				c->axes[i] = SDL_JoystickGetAxis(c->gc, i);
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

	// joystick not available
	// std::cout << "Joystick with id " << joystickId << " is not available" << std::endl;
	return false;
}
bool Joystick::GetButtonDown(int joystickId, Button button)
{
	auto it = availableJoysticks.find(joystickId);

	if (it != availableJoysticks.end())
	{
		return  it->second->buttons[static_cast<int>(button)] &&
			   !it->second->lastButtons[static_cast<int>(button)]; // check if it's not last button (not hold)
	}

	// joystick not available
	// std::cout << "Joystick with id " << joystickId << " is not available" << std::endl;
	return false;
}
bool Joystick::GetButtonUp(int joystickId, Button button)
{
	auto it = availableJoysticks.find(joystickId);

	if (it != availableJoysticks.end())
	{
		return !it->second->buttons[static_cast<int>(button)] &&
				it->second->lastButtons[static_cast<int>(button)]; // check if it's not last button (not hold)
	}

	// joystick not available
	// std::cout << "Joystick with id " << joystickId << " is not available" << std::endl;
	return false;
}
float Joystick::GetAxis(int joystickId, Axis axis)
{
	auto it = availableJoysticks.find(joystickId);

	if (it != availableJoysticks.end())
	{
		return it->second->axes[static_cast<int>(axis)];
	}

	// joystick not available

	return 0.f;
}
int Joystick::GetNextFreeIndex()
{
	int ret = -1;

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (availableJoysticks.count(i) == 0) {
			ret = i;
			break;
		}
	}

	return ret;
}