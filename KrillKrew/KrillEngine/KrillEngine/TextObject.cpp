#include "pch.h"
#include "TextObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

TextObject::TextObject()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


TextObject::~TextObject()
{

}

void TextObject::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo*squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint modeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	glBindTexture(GL_TEXTURE_2D, texture);

	if (modelMatixId == -1) {
		std::cout << "Error: Can't perform transformation " << std::endl;
		return;
	}

	glm::mat4 currentMatrix = this->getTransform();

	

	if (squareMesh != nullptr) {
		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(modeId, 1);
		squareMesh->ChangeTextureData(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		squareMesh->Render();
		glBindTexture(GL_TEXTURE_2D, 0);
	}



}

void TextObject::update(float deltaTime)
{
}

void TextObject::loadText(std::string text, SDL_Color textColor, int fontSize)
{
	/*glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	TTF_Font* font = TTF_OpenFont("../Resource/Font/Debrosee-ALPnL.ttf", fontSize);

	if (font)
	{
		std::cout << "Have font." << std::endl;
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), textColor);
		//SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(surfaceMessage, SDL_PIXELFORMAT_RGBA32, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfaceMessage->w, surfaceMessage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surfaceMessage->pixels);
		this->SetSize(surfaceMessage->w, -surfaceMessage->h);
		SDL_FreeSurface(surfaceMessage);
		//SDL_FreeSurface(formattedSurface);
		TTF_CloseFont(font);
	}
	else
	{
		std::cout << "Error font: " << TTF_GetError() << std::endl;
		return;
	}*/

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	TTF_Font* font = TTF_OpenFont("../Resource/Font/Debrosee-ALPnL.ttf", fontSize);
	if (font)
	{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), textColor);
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(surfaceMessage, SDL_PIXELFORMAT_RGBA32, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formattedSurface->w, formattedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);
		this->SetSize(formattedSurface->w, -formattedSurface->h);
		SDL_FreeSurface(formattedSurface);
		TTF_CloseFont(font);
	}
	else
	{
		std::cout << "Error: " << TTF_GetError() << std::endl;
		return;
	}
	
}

void TextObject::InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1) {
		std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return;
	}

	std::cout << "TextObject : Initialize SDL successful" << std::endl;
	return;
}

void TextObject::cleanSDL() {
	TTF_Quit();
	SDL_Quit();
}