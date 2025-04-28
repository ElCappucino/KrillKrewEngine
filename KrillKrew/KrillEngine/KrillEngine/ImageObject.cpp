
#include "ImageObject.h"



ImageObject::ImageObject()
{
	this->isAnimated = false;
	this->texture = 0;
	spriteRenderer = new SpriteRenderer("");
}


ImageObject::~ImageObject()
{
	delete spriteRenderer;
	spriteRenderer = nullptr;
}

void ImageObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
	
}
void ImageObject::SetSpriteInfo(SpritesheetInfo info)
{
	spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	this->SetTexture(info.texture);
}
void ImageObject::SetTextureWithID(SpritesheetInfo info, unsigned int id)
{
	texture = id;
	spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	
}
SpriteRenderer* ImageObject::GetSpriteRenderer()
{
	return spriteRenderer;
}

void ImageObject::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo *squareMesh = dynamic_cast<SquareMeshVbo *> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

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

void ImageObject::SetIsAnimated(bool value)
{
	this->isAnimated = value;
}
bool ImageObject::GetIsAnimated()
{
	return isAnimated;
}

void ImageObject::OnColliderEnter(Collider* other)
{

}
void ImageObject::OnColliderStay(Collider* other)
{

}
void ImageObject::OnColliderExit(Collider* other)
{

}
void ImageObject::OnTriggerEnter(Collider* other)
{

}
void ImageObject::OnTriggerStay(Collider* other)
{

}
void ImageObject::OnTriggerExit(Collider* other)
{

}

