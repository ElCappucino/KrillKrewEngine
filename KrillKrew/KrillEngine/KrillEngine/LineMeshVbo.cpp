
#include "LineMeshVbo.h"

std::string const LineMeshVbo::MESH_NAME = "line";

void LineMeshVbo::LoadData()
{
	LoadQuadData();
}

LineMeshVbo::LineMeshVbo()
{
}

std::string LineMeshVbo::GetMeshName()
{
	return MESH_NAME;
}

void LineMeshVbo::Render()
{
	BindVertexAndTextureData();
	// Draw the filled square

	// glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	// Draw the border as a line loop
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}