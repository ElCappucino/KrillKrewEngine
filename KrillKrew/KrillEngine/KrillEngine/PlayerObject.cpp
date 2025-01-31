
#include "PlayerObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"


PlayerObject::PlayerObject()
{
	this->isShooting = false;
	this->isAiming = false;
	this->isFacingLeft = true;
	this->number = 0;
	this->slowness = 2;
	this->durationSlowness = 0;
	this->isSlowness = false;
	this->pos = glm::vec3(0, 0, 0);

	currAnimState = AnimationState::Idle;

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
	xIsPositive = isPositiveX;
	yIsPositive = isPositiveY;

	if (!isPositiveX) {
		axisX = -axisX;
	}
	if (!isPositiveY) {
		axisY = -axisY;
	}
	/*cout << " X | " << axisX << endl;
	cout << " Y | " << axisY << endl;*/
	if (isDash) {
		velocity = glm::vec3(axisX * 5.f, axisY * 5.f, 0) * dashSpeed;
	}

	else if (isSlowness) {
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

bool PlayerObject::getXIsPositive() 
{
	return xIsPositive;
}

bool PlayerObject::getYIsPositive() 
{
	return yIsPositive;
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

bool PlayerObject::getIsAiming() 
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
void PlayerObject::reduceCooldown(int skill) 
{
	/*for (int i = 0; i < 3; i++) {
		if (cooldown[skill] > 0) {
			cooldown[skill] -= 1;
			std::cout << "Skill" << i << " " << getCooldown(i) << std::endl;
		}
	}*/

	cooldown[skill] -= 1;
	std::cout << "Skill" << skill << " " << getCooldown(skill) << std::endl;

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

void PlayerObject::setIsDash(bool isDash) {
	this->isDash = isDash;
}

bool PlayerObject::getIsDash() {
	return isDash;
}

void PlayerObject::setDurationDash(int time) {
	durationDash = time;
}

void PlayerObject::reduceDurationDash() {
	durationDash -= 1;
}

float PlayerObject::getDurationDash() {
	return durationDash;
}

void PlayerObject::UpdateFacingSide(bool isLeft)
{
	if (isLeft && isFacingLeft == false || !isLeft && isFacingLeft == true)
	{
		this->size.x = this->size.x * -1;
		isFacingLeft = isLeft;
	}
}
void PlayerObject::SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo)
{
	animList.insert({ state, spriteInfo });
}
void PlayerObject::ChangeAnimationState(AnimationState anim)
{
	if (currAnimState != anim)
	{
		currAnimState = anim;
		this->SetSpriteInfo(animList.find(anim)->second);
		this->spriteRenderer->SetTexture(animList.find(anim)->second.texture);
		this->SetTexture(animList.find(anim)->second.texture);
		this->spriteRenderer->ShiftTo(0, 0);
	}

	/*std::cout << "Player " << number << " height width = " << std::endl;
	std::cout << this->spriteRenderer->GetSheetHeight() << this->spriteRenderer->GetSheetWidth() << std::endl;
	std::cout << this->spriteRenderer->GetSpriteHeight() << this->spriteRenderer->GetSpriteWidth() << std::endl;*/
}
void PlayerObject::UpdateCurrentAnimation()
{
	if (abs(this->velocity.x) > 0 || abs(this->velocity.y > 0) && currAnimState != AnimationState::Running)
	{
		ChangeAnimationState(AnimationState::Running);
	}
	else if (abs(this->velocity.x) <= 0 || abs(this->velocity.y <= 0) && currAnimState == AnimationState::Running)
	{
		ChangeAnimationState(AnimationState::Idle);
	}
}

void PlayerObject::setAbility(int numberAbility, int idAbility) {
	abilities[numberAbility] = idAbility;
}

int PlayerObject::getIdAbility(int numberAbility) {
	return abilities[numberAbility];
}

void PlayerObject::setIsKnockback(bool isKnockback) {
	this->isKnockback = isKnockback;
}

void PlayerObject::setDurationKnockback(int time){
	durationKnockback = time;
}

void PlayerObject::reduceDurationKnockback(){
	durationKnockback -= 1;
}

bool PlayerObject::getIsKnockback() {
	return isKnockback;
}

float PlayerObject::getDurationKnockback(){
	return durationKnockback;
}