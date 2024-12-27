
#include "TrapObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"


TrapObject::TrapObject()
{
	collider = new Collider(Collider::Trigger, this);
	this->pos = glm::vec3(0, 0, 0);
}


TrapObject::~TrapObject()
{
}

void TrapObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void TrapObject::Render(glm::mat4 globalModelTransform)
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

void TrapObject::setLifeTime(int lifeTime) {
	this->lifeTime = lifeTime;
}

void TrapObject::reduceLifeTime() {
	lifeTime -= 1;
}
int TrapObject::getLifetime() {
	return lifeTime;
}

void TrapObject::setNumOwner(int num) {
	playerNumOwner = num;
}

int TrapObject::getNumOwner() {
	return playerNumOwner;
}

void TrapObject::OnColliderEnter(Collider* other)
{
	PlayerObject* player = dynamic_cast<PlayerObject*>(other->GetParent());
	if (player != nullptr)
	{
		if (this->getNumOwner() != player->GetPlayerNumber()) {
			Collider col1 = *this->GetCollider();
			Collider col2 = *player->GetCollider();

			glm::vec2 delta = glm::vec2(abs(this->getPos().x - player->getPos().x),
				abs(this->getPos().y - player->getPos().y));

			float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
			float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

			if (overlapX > 0 && overlapY > 0)
			{
				KK_TRACE("Trap of player {0} hit player {1}", this->getNumOwner(), player->GetPlayerNumber());
				player->SetSlowDuration(100);
				player->SetIsSlow(true);
				this->isActive = false;
			}
		}
	}
	
}
void TrapObject::OnColliderStay(Collider* other)
{

}
void TrapObject::OnColliderExit(Collider* other)
{

}
void TrapObject::OnTriggerEnter(Collider* other)
{

}
void TrapObject::OnTriggerStay(Collider* other)
{

}
void TrapObject::OnTriggerExit(Collider* other)
{

}