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
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define MAP_WIDTH 20
#define MAP_HEIGHT 16
