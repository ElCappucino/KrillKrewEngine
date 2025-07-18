
#include "GLRenderer.h"

GLRenderer::GLRenderer(int w, int h)
{
	this->winWidth = w;
	this->winHeight = h;
	SetOrthoProjection(-1.f, 1.f, -1.f, 1.f);
	glViewport(0, 0, winWidth, winHeight);
}
bool GLRenderer::InitGL(std::string vertexShaderFile, std::string fragmentShaderFile)
{
	// Initialize glew
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << std::endl;
		return false;
	}


	//Initialize OpenGL
	if (!Initialize(vertexShaderFile, fragmentShaderFile))
	{
		std::cout << "Unable to initialize OpenGL! " << std::endl;
		return false;
	}
	return true;
}

bool GLRenderer::Initialize(std::string vertexShaderFile, std::string fragmentShaderFile)
{
	//Success flag
	bool success = true;

	//Generate program
	gProgramId = glCreateProgram();
	vertexShader = new Shader(vertexShaderFile, GL_VERTEX_SHADER);
	if (!vertexShader->LoadSource()) {
		return false;
	}
	fragmentShader = new Shader(fragmentShaderFile, GL_FRAGMENT_SHADER);
	if (!fragmentShader->LoadSource()) {
		return false;
	}
	glAttachShader(gProgramId, vertexShader->getShaderId());
	glAttachShader(gProgramId, fragmentShader->getShaderId());


	//Link program
	glLinkProgram(gProgramId);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(gProgramId, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		std::cout << "Error linking program " << gProgramId << std::endl;
		PrintProgramLog(gProgramId);
		return false;
	}

	//Get vertex attribute location
	gPos2DLocation = glGetAttribLocation(gProgramId, "pos2D");
	if (gPos2DLocation == -1)
	{
		std::cout << "pos2D is not a valid glsl program variable" << std::endl;
		return false;
	}
	gTex2DLocation = glGetAttribLocation(gProgramId, "inTexCoord");
	if (gTex2DLocation == -1)
	{
		std::cout << "inTexCoord is not a valid glsl program variable" << std::endl;
		return false;
	}

	//Setting color uniform id
	colorUniformId = glGetUniformLocation(gProgramId, "color");
	if (colorUniformId == -1)
	{
		std::cout << "color is not a valid glsl uniform variable" << std::endl;
		return false;
	}

	//Set up uniform id attribute
	pMatrixId = glGetUniformLocation(gProgramId, "pMatrix");
	if (pMatrixId == -1)
	{
		std::cout << "pMatrix is not a valid glsl uniform variable" << std::endl;
		return false;
	}
	mMatrixId = glGetUniformLocation(gProgramId, "mMatrix");
	if (mMatrixId == -1)
	{
		std::cout << "mMatrix is not a valid glsl uniform variable" << std::endl;
		return false;
	}
	renderModeUniformId = glGetUniformLocation(gProgramId, "renderMode");
	if (renderModeUniformId == -1)
	{
		std::cout << "renderMode is not a valid glsl uniform variable" << std::endl;
		return false;
	}


	glEnableVertexAttribArray(gPos2DLocation);
	glEnableVertexAttribArray(gTex2DLocation);

	//Initialize clear color
	glClearColor(1.0f, 1.0f, 1.0f, 1.f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;

}

void GLRenderer::Render(std::vector <DrawableObject*> & objList)
{
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update window with OpenGL rendering

	glUseProgram(gProgramId);
	//Set up matrix uniform

	if (pMatrixId != -1) {
		glUniformMatrix4fv(pMatrixId, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));
	}

	glm::mat4 camera = glm::mat4(1.0);

	//std::cout << "Draw" << std::endl;
	for (DrawableObject *obj : objList) {
		obj->Render(camera);
	}

	//Unbind program
	glUseProgram(NULL);
}

void GLRenderer::SetMeshAttribId(MeshVbo * shape)
{
	shape->SetAttribId(gPos2DLocation, gTex2DLocation);
}

void GLRenderer::AddMesh(std::string name, MeshVbo * shape)
{
	SetMeshAttribId(shape);
	shapes[name] = shape;
}

MeshVbo * GLRenderer::GetMesh(std::string name)
{
	if (shapes.find(name) == shapes.end()) {
		return nullptr;
	}
	else {
		return shapes[name];
	}
}

OrthographicValue GLRenderer::GetOrthovalue()
{
	return this->orthoValue;
}

void GLRenderer::ClearMesh()
{
	for (std::map<std::string, MeshVbo*>::iterator it = shapes.begin(); it != shapes.end(); it++)
	{
		delete it->second;
	}
		
	shapes.clear();
}

void GLRenderer::PrintProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			std::cout << infoLog << std::endl;

		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

GLRenderer::~GLRenderer()
{
	if (gPos2DLocation != -1) {
		glDisableVertexAttribArray(gPos2DLocation);
	}
}

void GLRenderer::SetOrthoProjection(float left, float right, float bottom, float top)
{
	orthoValue.left = left;
	orthoValue.right = right;
	orthoValue.bottom = bottom;
	orthoValue.top = top;

	projectionMatrix = glm::ortho(left, right, bottom, top);
}

void GLRenderer::SetViewPort(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
}

void GLRenderer::SetClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0);
}

GLuint GLRenderer::GetModelMatrixAttrId()
{
	return this->mMatrixId;
}

GLuint GLRenderer::GetProjectionMatrixAttrId()
{
	return this->pMatrixId;
}

GLuint GLRenderer::GetColorUniformId()
{
	return this->colorUniformId;
}

GLuint GLRenderer::GetModeUniformId()
{
	return this->renderModeUniformId;
}

GLuint GLRenderer::LoadTexture(std::string path)
{
	glActiveTexture(GL_TEXTURE0);
	SDL_Surface *image = IMG_Load(path.c_str());
	if (image == NULL)
	{
		std::cerr << "IMG_Load: " << SDL_GetError() << std::endl;
		return -1;
	}
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int Mode = GL_RGB;
	if (image->format->BytesPerPixel == 4)
	{
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode, GL_UNSIGNED_BYTE, image->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	SDL_FreeSurface(image);

	return texture;
}