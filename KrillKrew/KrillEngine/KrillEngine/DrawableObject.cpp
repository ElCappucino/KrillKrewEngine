
#include "DrawableObject.h"
#include "GameEngine.h"

bool DrawableObject::ApplyTransform(glm::mat4 globalModelTransform)
{
    GLuint modelMatrixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();

    if (modelMatrixId == -1)
    {
        std::cout << "Error: Can't perform transformation" << std::endl;
        return false;
    }

    glm::mat4 currentMatrix = globalModelTransform * getTransform();

    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));

    return true;
}

bool DrawableObject::SetRenderMode(int renderMode)
{
    GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

    if (renderModeId == -1)
    {
        std::cout << "Error: Can't set renderMode" << std::endl;
        return false;
    }

    glUniform1i(renderModeId, renderMode);

    return true;
}

glm::mat4 DrawableObject::getTransform()
{
    glm::mat4 transform = glm::mat4(1.0);
    transform = glm::translate(transform, glm::vec3(pos.x, pos.y, 0));
    transform = glm::rotate(transform, rotateAngle, glm::vec3(0, 0, 1));
    transform = glm::scale(transform, glm::vec3(size.x, size.y, 1));

    return transform;
}

DrawableObject::DrawableObject()
{
    pos = glm::vec3(0.0, 0.0, 0.0);
    size = glm::vec3(1.0, 1.0, 1.0);
    rotateAngle = 0;

    orderingLayer = 0;
}

DrawableObject::~DrawableObject()
{
}

void DrawableObject::SetSize(float sizeX, float sizeY)
{
    size = glm::vec3(sizeX, sizeY, 1);
}

void DrawableObject::SetPosition(glm::vec3 newPosition)
{
    pos = newPosition;
}
void DrawableObject::SetRotation(float degree)
{
    rotateAngle = degree;
}
void DrawableObject::SetOrderingLayer(int layer)
{
    this->orderingLayer = layer;
}

void DrawableObject::Translate(glm::vec3 moveDistance)
{
    pos = pos + moveDistance;
}

glm::vec3 DrawableObject::getPos()
{

    return pos;
}

glm::vec3 DrawableObject::getSize()
{

    return size;
}
float DrawableObject::getOrderingLayer() const
{
    return orderingLayer;
}
bool DrawableObject::GetIsActive()
{
    return isActive;
}
void DrawableObject::SetIsActive(bool isActive)
{
    this->isActive = isActive;
}