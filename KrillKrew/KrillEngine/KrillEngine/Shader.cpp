
#include "Shader.h"

using namespace std;


GLuint Shader::getShaderId()
{
	return this->shaderId;
}

bool Shader::LoadSource()
{
	ifstream shaderFile(this->fileName);

	if (!shaderFile) {
		std::cout << "Can't open the shader file " << fileName << std::endl;
		return false;
	}
	else {


		string source((std::istreambuf_iterator<char>(shaderFile)),
			std::istreambuf_iterator<char>());

		shaderFile.close();

		// Print everything in that file
		//cout << "shader are " << source << endl;

		this->shaderId = glCreateShader(shaderType);
		const GLchar* shaderSource[] = { source.c_str() };

		//Set vertex source
		glShaderSource(this->shaderId, 1, shaderSource, NULL);

		//Compile vertex source
		glCompileShader(this->shaderId);

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(this->shaderId, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			std::cout << "Unable to compile shader " << this->shaderId << std::endl;
			PrintShaderLog();
			return  false;
		}
		else
		{
			return true;
		}
	}
}

void Shader::PrintShaderLog()
{
	//Make sure name is shader
	if (glIsShader(this->shaderId))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(this->shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(this->shaderId, maxLength, &infoLogLength, infoLog);
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
		std::cout << "Name " << this->shaderId << " is not a shader " << std::endl;
	}
}

Shader::Shader(std::string fileName, GLenum shaderType)
{
	this->fileName = fileName;
	this->shaderType = shaderType;
}

Shader::~Shader()
{
}
