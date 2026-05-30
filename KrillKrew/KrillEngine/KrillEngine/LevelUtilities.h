#pragma once

// Only using in the Level Class

// Core Classes

#include "GLRenderer.h"
#include "GameEngine.h"
#include "GameStateController.h"
#include "GameStateList.h"

// ImGui
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

// Object Classes

#include "DrawableObject.h"
#include "EntityObject.h"
#include "GameObject.h"
#include "GizmosObject.h"
#include "ImageObject.h"
#include "ParticleObject.h"
#include "PlayerGroundColliderObject.h"
#include "PlayerHitboxObject.h"
#include "PlayerObject.h"
#include "ProjectileObject.h"
#include "PropObject.h"
#include "TextObject.h"
#include "TileObject.h"
#include "TrapObject.h"
#include "UiObject.h"

// Vbo

#include "LineMeshVbo.h"
#include "MeshVbo.h"
#include "SquareMeshVbo.h"
#include "TriangleMeshVbo.h"

// Component

#include "Camera.h"
#include "Collider.h"
#include "InfoStruct.h"
#include "Joystick.h"
#include "Log.h"
#include "Shader.h"
#include "SoundManager.h"
#include "Timer.h"

// Library
#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>s

#define MAP_WIDTH 20
#define MAP_HEIGHT 16

enum MenuButtonName_
{
    MenuButtonName_None,
    MenuButtonName_GameName,
    MenuButtonName_StartButton,
    MenuButtonName_TutorialButton,
    MenuButtonName_OptionButton,
    MenuButtonName_ExitButton,

    MenuButtonName_DisplayType,
    MenuButtonName_DisplayDropdown,

    MenuButtonName_DisplayType_Text,
    MenuButtonName_MasterVolume_Text,
    MenuButtonName_SFXVolume_Text,
    MenuButtonName_BGMVolume_Text,

    MenuButtonName_MasterVolume_Track,
    MenuButtonName_SFXVolume_Track,
    MenuButtonName_BGMVolume_Track,

    MenuButtonName_MasterVolume_Knob,
    MenuButtonName_SFXVolume_Knob,
    MenuButtonName_BGMVolume_Knob,

    MenuButtonName_MasterVolume_Box,
    MenuButtonName_SFXVolume_Box,
    MenuButtonName_BGMVolume_Box,

    MenuButtonName_AreYouSureStart_Yes,
    MenuButtonName_AreYouSureStart_No,
    MenuButtonName_AreYouSureExit_Yes,
    MenuButtonName_AreYouSureExit_No,

    MenuButtonName_TextOption,
    MenuButtonName_Display,
    MenuButtonName_VolumeTrack
};
