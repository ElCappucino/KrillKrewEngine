#pragma once
#include "MeshVbo.h"

/// @brief The class for store the Vbo data of square mesh
class TileMeshVbo : public MeshVbo {
protected:

public:
	static string const MESH_NAME;
	TileMeshVbo();
	virtual string GetMeshName();
	virtual void Render();
	virtual void LoadData();
	virtual void LoadData(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
};