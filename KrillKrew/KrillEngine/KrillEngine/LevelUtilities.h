#pragma once

// Only using in the Level Class

// Core Classes

#include "GameEngine.h"
#include "GameStateController.h"
#include "GameStateList.h"
#include "GLRenderer.h"

// ImGui
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

// Object Classes

#include "DrawableObject.h"
#include "TextObject.h"
#include "EntityObject.h"
#include "GameObject.h"
#include "GizmosObject.h"
#include "ImageObject.h"
#include "PlayerObject.h"
#include "ProjectileObject.h"
#include "TrapObject.h"
#include "UiObject.h"
#include "TileObject.h"
#include "PlayerHitboxObject.h"
#include "PlayerGroundColliderObject.h"
#include "PropObject.h"
#include "ParticleObject.h"
#include "TextObject.h"

// Vbo

#include "LineMeshVbo.h"
#include "SquareMeshVbo.h"
#include "TriangleMeshVbo.h"
#include "MeshVbo.h"

// Component

#include "Camera.h"
#include "Collider.h"
#include "Joystick.h"
#include "Log.h"
#include "Shader.h"
#include "Timer.h"
#include "InfoStruct.h"
#include "SoundManager.h"

// Library
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <bitset>
#include <functional>
#include <cmath>
#include <array>
#include <memory>
#include <unordered_map>
#include <math.h>
#include <chrono>
#include <set>
#include <unordered_set>
#include <queue>
#include <numeric>
#include <cstdlib>
#include <thread>

#define MAP_WIDTH  20
#define MAP_HEIGHT 16




