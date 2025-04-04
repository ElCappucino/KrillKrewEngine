
#include "GizmosObject.h"


GizmosObject::GizmosObject()
{
	borderColor = glm::vec3(0.0, 0.0, 0.0);

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
	// std::cout << "Hello" << std::endl;
	LineMeshVbo* squareMesh = dynamic_cast<LineMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(LineMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint colorId = GameEngine::GetInstance()->GetRenderer()->GetColorUniformId();
	GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	if (modelMatixId == -1) {
		std::cout << "Error: Can't perform transformation " << std::endl;
		return;
	}
	if (colorId == -1) {
		std::cout << "Error: Can't set color " << std::endl;
		return;
	}
	if (renderModeId == -1) {
		std::cout << "Error: Can't set renderMode in ImageObject " << std::endl;
		return;
	}
	//vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, borderColor.x, borderColor.y, borderColor.z); // Set the fill color
		glUniform1i(renderModeId, 0); // Set the render mode for filled polygons
		squareMesh->Render();

		// Render the border
		//glUniform3f(colorId, borderColor.x, borderColor.y, borderColor.z); // Set the border color
		//glUniform1i(renderModeId, 1); // Set the render mode for line drawing
		//squareMesh->Render();

	}
}

