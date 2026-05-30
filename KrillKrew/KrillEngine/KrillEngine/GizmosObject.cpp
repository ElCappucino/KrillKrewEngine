
#include "GizmosObject.h"


GizmosObject::GizmosObject()
{
	borderColor = glm::vec3(0.0, 0.0, 0.0);
	this->rotateAngle = 0;
	this->orderingLayer = 3;
}


GizmosObject::~GizmosObject()
{
}

void GizmosObject::SetColor(float r, float g, float b)
{
	borderColor = glm::vec3(r, g, b);
}

void GizmosObject::Render(glm::mat4 globalModelTransform)
{
    LineMeshVbo* lineMesh = dynamic_cast<LineMeshVbo*>(GameEngine::GetInstance()->GetRenderer()->GetMesh(LineMeshVbo::MESH_NAME));

    if (lineMesh == nullptr)
    {
        return;
    }

    if (!ApplyTransform(globalModelTransform))
    {
        return;
    }

    if (!SetRenderMode(0))
    {
        return;
    }

    GLuint colorId = GameEngine::GetInstance()->GetRenderer()->GetColorUniformId();

    if (colorId == -1)
    {
        std::cout << "Error: Can't set color in GizmosObject" << std::endl;
        return;
    }

    glUniform3f(colorId, borderColor.x, borderColor.y, borderColor.z);

    lineMesh->Render();
}

