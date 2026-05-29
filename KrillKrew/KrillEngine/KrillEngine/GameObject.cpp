
#include "GameObject.h"



GameObject::GameObject()
{
	color = glm::vec3(0.0, 0.0, 0.0);
}


GameObject::~GameObject()
{
}

void GameObject::SetColor(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}

void GameObject::Render(glm::mat4 globalModelTransform)
{
    SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*>(GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

    if (squareMesh == nullptr)
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
        std::cout << "Error: Can't set color in GameObject" << std::endl;
        return;
    }

    glUniform3f(colorId, color.x, color.y, color.z);

    squareMesh->Render();
}

