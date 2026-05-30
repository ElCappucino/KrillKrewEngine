#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "LineMeshVbo.h"
#include "GameObject.h"
#include "ImageObject.h"
#include "Camera.h"
#include "Joystick.h"
#include "Timer.h"
#include <math.h>
#include <map>
#include <chrono>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

class EntityObject;

/// @brief The class for setup object in the level
/// @brief It intent to inherit this class for creating any new unique scene.
class Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::vector<DrawableObject*> UIsList;
	
	ImageObject * player;
	Camera camera;

	float dt = 0;
protected:
	template <size_t Height, size_t Width>
	void TileImport(std::array<std::array<int, Width>, Height>& tileBuffer, const std::string& fileName)
	{
		std::ifstream mapFile(fileName);
		std::string line;
		size_t counter = 0;

		if (!mapFile.is_open())
		{
			std::cout << "Error: reading tile information" << std::endl;
			return;
		}

		while (std::getline(mapFile, line, ',') && counter < Height * Width)
		{
			tileBuffer[counter / Width][counter % Width] = std::stoi(line);
			counter++;
		}
	}
public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate();
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();
	virtual void Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);

	virtual void AddEntityToScene(EntityObject* entity);
	virtual void AddObjectToScene(DrawableObject* object);
};
