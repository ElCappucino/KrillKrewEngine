#pragma once

#include "MeshVbo.h"

/// @brief The class for store the Vbo data of square mesh
class SquareMeshVbo : public MeshVbo {
protected:

public:
	static string const MESH_NAME;
	SquareMeshVbo();
	virtual string GetMeshName();
	virtual void Render();
	virtual void LoadData();
};