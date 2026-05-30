
#include "SquareMeshVbo.h"

std::string const SquareMeshVbo::MESH_NAME = "square";

void SquareMeshVbo::LoadData()
{
    LoadQuadData();
}

void SquareMeshVbo::ChangeTextureData(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight)
{

    GLfloat texData[] = {column * spritewidth / sheetwidth,
                         row * spriteheight / sheetheight,
                         (column + 1) * spritewidth / sheetwidth,
                         row * spriteheight / sheetheight,
                         (column + 1) * spritewidth / sheetwidth,
                         (row + 1) * spriteheight / sheetheight,
                         column * spritewidth / sheetwidth,
                         (row + 1) * spriteheight / sheetheight};

    glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), texData, GL_STATIC_DRAW);
}

SquareMeshVbo::SquareMeshVbo()
{
}

std::string SquareMeshVbo::GetMeshName()
{
    return MESH_NAME;
}

void SquareMeshVbo::Render()
{
    BindVertexAndTextureData();
    // Draw the filled square

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Draw the border as a line loop
    // glDrawArrays(GL_LINE_LOOP, 0, 4);
}