#pragma once

#include <string>
#include <GL\glew.h>

/// @brief The class for store the shader data
class Shader
{
	GLuint shaderId;
	std::string fileName;
	GLenum shaderType;

public:
	/// @brief The getter of the shader id.
	/// @return it will return the shader id.
	GLuint getShaderId();
	/// @brief The function using for reading shader information and setup shaderId.
	/// @return This function returns true if it compile completely. false if there is error.
	bool LoadSource();
	/// @brief The function for print the information log of shader.
	/// @brief It will print error if it's not a shader.
	void PrintShaderLog();
	/// @brief The constructor. Using for setup the shader information.
	/// @param fileName describes shader information's file name.
	/// @param shaderType describes shader type using GLenum type. 
	Shader(std::string fileName, GLenum shaderType);
	/// @brief The destructor.
	/// @note There is no any command.
	~Shader();
};