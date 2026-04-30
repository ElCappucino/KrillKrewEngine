#pragma once
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_gamecontroller.h"

#include <array>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "Log.h"

class Joystick
{
public:
    // Aligned with SDL_GameControllerAxis
    enum class Axis
    {
        LeftStickHorizontal = SDL_CONTROLLER_AXIS_LEFTX,
        LeftStickVertical = SDL_CONTROLLER_AXIS_LEFTY,
        RightStickHorizontal = SDL_CONTROLLER_AXIS_RIGHTX,
        RightStickVertical = SDL_CONTROLLER_AXIS_RIGHTY,
        LeftTrigger = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
        RightTrigger = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
        Count
    };

    // PS-style naming, internally mapped to SDL
    enum class Button
    {
        Cross = SDL_CONTROLLER_BUTTON_A,             // A (Xbox), Cross (PS)
        Circle = SDL_CONTROLLER_BUTTON_B,             // B (Xbox), Circle (PS)
        Square = SDL_CONTROLLER_BUTTON_X,             // X (Xbox), Square (PS)
        Triangle = SDL_CONTROLLER_BUTTON_Y,             // Y (Xbox), Triangle (PS)
        ShareButton = SDL_CONTROLLER_BUTTON_BACK,          // Back/Share
        P5Button = SDL_CONTROLLER_BUTTON_GUIDE,         // PS / Xbox Logo
        OptionsButton = SDL_CONTROLLER_BUTTON_START,         // Start/Options
        LeftStickDown = SDL_CONTROLLER_BUTTON_LEFTSTICK,
        RightStickDown = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
        L1 = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        R1 = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        DPAD_Up = SDL_CONTROLLER_BUTTON_DPAD_UP,
        DPAD_Down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        DPAD_Left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        DPAD_Right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        Touchpad = SDL_CONTROLLER_BUTTON_TOUCHPAD,      // Only on PS controllers
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

        std::array<bool, static_cast<int>(Button::Count)> buttons;
        std::array<bool, static_cast<int>(Button::Count)> lastButtons;
        std::array<float, static_cast<int>(Axis::Count)> axes;
        std::array<float, static_cast<int>(Axis::Count)> lastAxes;
    };

    static std::unordered_map<int, std::unique_ptr<Controller>> availableJoysticks;
};
