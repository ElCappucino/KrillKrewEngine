
#include "PlayerObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"


PlayerObject::PlayerObject()
{
	
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void PlayerObject::Render(glm::mat4 globalModelTransform)
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

	squareMesh->ChangeTextureData(spriteRenderer->GetRow(),
		spriteRenderer->GetColumn(),
		spriteRenderer->GetSpriteWidth(),
		spriteRenderer->GetSpriteHeight(),
		spriteRenderer->GetSheetWidth(),
		spriteRenderer->GetSheetHeight());

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

void PlayerObject::setVelocity(float axisX, float axisY , bool isPositiveX, bool isPositiveY) 
{

	if (!isPositiveX) {
		axisX = -axisX;
	}
	if (!isPositiveY) {
		axisY = -axisY;
	}
	/*cout << " X | " << axisX << endl;
	cout << " Y | " << axisY << endl;*/
	if (isSlowness) {
		velocity = glm::vec3(axisX * 5.f, axisY * 5.f, 0) / slowness;
	}
	else 
	{
		velocity = glm::vec3(axisX * 5.f, axisY * 5.f, 0);
	}
	
}

glm::vec3 PlayerObject::getVelocity()
{
	return velocity;
}

void PlayerObject::setIsShooting(bool isShoot) 
{
	isShooting = isShoot;
}
bool PlayerObject::getIsShooting() 
{
	return isShooting;
}

void PlayerObject::setIsAiming(bool isAim) 
{
	isAiming = isAim;
}

bool  PlayerObject::getIsAiming() 
{
	return isAiming;
}

Collider* PlayerObject::GetCollider()
{
	return collider;
}

void PlayerObject::OnColliderEnter(Collider* other)
{
	// Base
	EntityObject::OnColliderEnter(other);

	// Behavior
}
void PlayerObject::OnColliderStay(Collider* other)
{
	// Base
	EntityObject::OnColliderStay(other);

	// Behavior
}
void PlayerObject::OnColliderExit(Collider* other)
{
	// Base
	EntityObject::OnColliderExit(other);

	// Behavior
}
void PlayerObject::OnTriggerEnter(Collider* other)
{
	// Base
	EntityObject::OnTriggerEnter(other);

	// Behavior
}
void PlayerObject::OnTriggerStay(Collider* other)
{
	// Base
	EntityObject::OnTriggerStay(other);

	// Behavior
}
void PlayerObject::OnTriggerExit(Collider* other)
{
	// Base
	EntityObject::OnTriggerExit(other);

	// Behavior
	return hitbox;
}

void PlayerObject::setNumber(int num) 
{
	number = num;
}

int PlayerObject::getNumber()
{
	return number;
}

void PlayerObject::setCooldown(int skill, int time) 
{
	cooldown[skill] = time;
}
void PlayerObject::reduceCooldown() 
{
	for (int i = 0; i < 3; i++) {
		if (cooldown[i] > 0) {
			cooldown[i] -= 1;
			std::cout << "Skill" << i << " " << getCooldown(i) << std::endl;
		}
	}
}
float PlayerObject::getCooldown(int skill) 
{
	return cooldown[skill];
}

void PlayerObject::setDurationSlowness(int time) 
{
	durationSlowness = time;
}
void PlayerObject::reduceDurationSlowness()
{
	
	durationSlowness -= 1;
	std::cout << "durationSlowness player" << getNumber() << " " << durationSlowness << std::endl;
	
}

void PlayerObject::setIsSlowness(bool isSlow)
{
	isSlowness = isSlow;
}

float PlayerObject::getDurationSlowness() 
{
	return durationSlowness;
}

bool PlayerObject::getIsSlowness()
{
	return isSlowness;
}