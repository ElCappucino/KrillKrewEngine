#pragma once
#include "SDL.h"
#include <array>
#include <memory>
#include <unordered_map>

class Joystick
{
public:
	// Adapt from SDL - SDL_GameControllerAxis
	enum class Axis
	{
        LeftStickHorizontal,
        LeftStickVertical,
        RightStickHorizontal,
        RightStickVertical,
        LeftTrigger,
        RightTrigger,
        Count
	};

    // Adapt from SDL - SDL_GameControllerButton
    enum class Button
    {
       A,
       B,
       X,
       Y,
       Back,
       Guide,
       Start,
       LS,
       RS,
       LB,
       RB,
       DPAD_Up,
       DPAD_Down,
       DPAD_Left,
       DPAD_Right,
       Count
    };

    static void OnJoystickConnected(SDL_ControllerDeviceEvent& e);
    static void OnJoystickDisconnected(SDL_ControllerDeviceEvent& e);
    static void Shutdown();
    static void Update();
    static bool GetButton(int joystickId, Button button);
    static bool GetButtonDown(int joystickId, Button button);
    static bool GetButtonUp(int joystickId, Button button);
    static float GetAxis(int joystickId, Axis axis);

private:

    static int GetNextFreeIndex();

    struct Controller
    {
        int joystickIndex = -1;
        SDL_GameController* gc = nullptr;

        std::array<bool, (int)Button::Count> buttons;
        std::array<bool, (int)Button::Count> lastButtons;
        std::array<float, (int)Axis::Count> axes; // -1 to 1
        std::array<float, (int)Axis::Count> lastAxes;
    };

    static std::unordered_map<int, std::unique_ptr<Controller>> availableJoysticks;
};