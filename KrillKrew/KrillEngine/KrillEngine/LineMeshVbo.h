#pragma once

#include "GameEngine.h"
#include "MeshVbo.h"

/// @brief The class for store the Vbo data of square mesh
class LineMeshVbo : public MeshVbo
{
protected:
public:
    static std::string const MESH_NAME;
    LineMeshVbo();
    virtual std::string GetMeshName();
    virtual void Render();
    virtual void LoadData();
};