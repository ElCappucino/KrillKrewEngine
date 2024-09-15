#pragma once

#include "MeshVbo.h"

/// @brief The class for store the Vbo data of triangle mesh
class TriangleMeshVbo : public MeshVbo {
protected:

public:
	static string const MESH_NAME;
	TriangleMeshVbo();
	virtual string GetMeshName();
	virtual void Render();
	virtual void LoadData();
};