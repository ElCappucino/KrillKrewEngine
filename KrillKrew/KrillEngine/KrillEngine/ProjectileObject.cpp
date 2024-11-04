
#include "ProjectileObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"


ProjectileObject::ProjectileObject()
{

}


ProjectileObject::~ProjectileObject()
{
}

void ProjectileObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void ProjectileObject::SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight) {
	sheetInfo.row = row;
	sheetInfo.column = column;
	sheetInfo.spritewidth = spritewidth;
	sheetInfo.spriteheight = spriteheight;
	sheetInfo.sheetwidth = sheetwidth;
	sheetInfo.sheetheight = sheetheight;
}

void ProjectileObject::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	if (modelMatixId == -1) {
		std::cout << "Error: Can't perform transformation " << std::endl;
		return;
	}
	if (renderModeId == -1) {
		std::cout << "Error: Can't set renderMode in ImageObject " << std::endl;
		return;
	}

	squareMesh->ChangeTextureData(sheetInfo.row, sheetInfo.column, sheetInfo.spritewidth, sheetInfo.spriteheight, sheetInfo.sheetwidth, sheetInfo.sheetheight);

	std::vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->Render();

	}
}

void ProjectileObject::setVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {

	if (!isPositiveX) {
		axisX = -axisX;
	}
	if (!isPositiveY) {
		axisY = -axisY;
	}
	velocity = glm::vec3(axisX * 5.f, axisY * 5.f, 0);

}

glm::vec3 ProjectileObject::getVelocity() {
	return velocity;
}

void ProjectileObject::setLifeTime(int lifeTime) {
	this->lifeTime = lifeTime;
}

void ProjectileObject::reduceLifeTime() {
	lifeTime -= 1;
}
int ProjectileObject::getLifetime() {
	return lifeTime;
}

void ProjectileObject::setNumOwner(int num) {
	playerNumOwner = num;
}

int ProjectileObject::getNumOwner() {
	return playerNumOwner;
}