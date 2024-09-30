
#include "ImageObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"


ImageObject::ImageObject()
{

}


ImageObject::~ImageObject()
{
}

void ImageObject::SetTexture(string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void ImageObject::SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight) {
	sheetInfo.row = row;
	sheetInfo.column = column;
	sheetInfo.spritewidth = spritewidth;
	sheetInfo.spriteheight = spriteheight;
	sheetInfo.sheetwidth = sheetwidth;
	sheetInfo.sheetheight = sheetheight;
}

void ImageObject::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo *squareMesh = dynamic_cast<SquareMeshVbo *> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (renderModeId == -1) {
		cout << "Error: Can't set renderMode in ImageObject " << endl;
		return;
	}

	squareMesh->ChangeTextureData(sheetInfo.row, sheetInfo.column, sheetInfo.spritewidth, sheetInfo.spriteheight, sheetInfo.sheetwidth, sheetInfo.sheetheight);

	vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->Render();

	}
}

