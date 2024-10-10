//#include "Joystick.h"
//
//#include <algorithm>
//#include <iostream>
//
//#include "SDL_events.h"
//#include "SDL_gamecontroller.h"
//
//void Joystick::OnJoystickConnected(SDL_ControllerDeviceEvent& e) 
//{
//	int deviceIndex = e.which;
//	if (SDL_IsGameController(deviceIndex)) 
//	{
//		auto c = std::make_unique<Controller>();
//		c->gc = SDL_GameControllerOpen(deviceIndex);
//		if (c->gc)
//		{
//			c->joystickIndex = deviceIndex;
//
//			std::fill(c->buttons.begin(),		c->buttons.end(),		false);
//			std::fill(c->lastButtons.begin(),	c->lastButtons.end(),	false);
//			std::fill(c->axes.begin(),			c->axes.end(),			0.f);
//			std::fill(c->lastAxes.begin(),		c->lastAxes.end(),		0.f);
//
//			int mapIndex = GetNextFreeIndex();
//
//			std::cout << "Joystick Connected: Mapindex: " << mapIndex << " DeviceIndex: " << deviceIndex << std::endl;
//
//			availableJoysticks[mapIndex] = std::move(c);
//		}
//		else {
//			std::cout << "Error: Unable to Connect joystick with the Device index : " << deviceIndex << std::endl;
//		}
//	}
//}
//void Joystick::OnJoystickDisconnected(SDL_ControllerDeviceEvent& e)
//{
//	int deviceIndex = e.which;
//	for (auto it = availableJoysticks.begin(); it != availableJoysticks.end(); it++) 
//	{
//		Controller* c = it->second.get();
//		if (c->joystickIndex == deviceIndex)
//		{
//			SDL_GameControllerClose(c->gc);
//			availableJoysticks.erase(it);
//			break;
//		}
//	}
//}
//void Joystick::Shutdown()
//{
//	for (auto it = availableJoysticks.begin(); it != availableJoysticks.end();)
//	{
//		Controller* c = it->second.get();
//		SDL_GameControllerClose(c->gc);
//		availableJoysticks.erase(it);
//	}
//}
//void Joystick::Update()
//{
//
//}
//bool Joystick::GetButton(int joystickId, Button button)
//{
//
//}
//bool Joystick::GetButtonDown(int joystickId, Button button)
//{
//
//}
//bool Joystick::GetButtonUp(int joystickId, Button button)
//{
//
//}
//float Joystick::GetAxis(int joystickId, Axis axis)
//{
//
//}
//int Joystick::GetNextFreeIndex()
//{
//	int ret = -1;
//
//	for (int i = 0; i < SDL_NumJoysticks(); i++)
//	{
//		if (availableJoysticks.count(i) == 0) {
//			ret = i;
//			break;
//		}
//	}
//
//	return ret;
//}