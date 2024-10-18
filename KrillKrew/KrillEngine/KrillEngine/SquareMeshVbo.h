#pragma once

#include "MeshVbo.h"
#include "GameEngine.h"

/// @brief The class for store the Vbo data of square mesh
class SquareMeshVbo : public MeshVbo {
protected:

public:
	static std::string const MESH_NAME;
	SquareMeshVbo();
	virtual std::string GetMeshName();
	virtual void Render();
	virtual void LoadData();
	void ChangeTextureData(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
};