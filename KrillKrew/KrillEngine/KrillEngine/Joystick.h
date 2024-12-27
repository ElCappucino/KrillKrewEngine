#pragma once
#include "SDL.h"
#include <array>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "SDL_events.h"
#include "SDL_gamecontroller.h"

class Joystick
{
public:
	// This reference from PS5 controller config
	enum class Axis
	{
        LeftStickHorizontal = 0,
        LeftStickVertical,
        RightStickHorizontal,
        RightStickVertical,
        LeftTrigger,
        RightTrigger,
        Count
	};

    // This reference from PS5 controller config
    enum class Button
    {
        // Debug Version
       /*Square = 0,
       Cross,
       Circle,
       Triangle,
       L1,
       R1,
       L2,
       R2,
       DPAD_Up,
       DPAD_Down,
       DPAD_Left,
       DPAD_Right,
       LeftStickUp,
       RightStickUp,
       LeftStickDown,
       RightStickDown,
       LeftStickLeft,
       RightSticLeft,
       LeftStickRight,
       RightStickRight,
       P5Button,
       ShareButton,
       OptionsButton,
       Count*/
        
       // Release Version
       Cross = 0,
       Circle,
       Square,
       Triangle,
       ShareButton,
       P5Button,
       OptionsButton,
       LeftStickDown,
       RightStickDown,
       L1,
       R1,
       DPAD_Up,
       DPAD_Down,
       DPAD_Left,
       DPAD_Right,
       Touchpad,    
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
        SDL_Joystick* gc = nullptr;

        std::array<bool, (int)Button::Count> buttons;
        std::array<bool, (int)Button::Count> lastButtons;
        std::array<float, (int)Axis::Count> axes; // -1 to 1
        std::array<float, (int)Axis::Count> lastAxes;
    };

    static std::unordered_map<int, std::unique_ptr<Controller>> availableJoysticks;
};