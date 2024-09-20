#pragma once

#include <iostream>
#include <GL\glew.h>
#include "Shader.h"
#include <map>
#include <vector>
#include <string>
#include "MeshVbo.h"
#include "glm.hpp"
#include "DrawableObject.h"


using namespace std;

/// @brief This class is for rendering any drawable object
/// @see DrawableObject
class GLRenderer
{
protected:
	int winWidth;
	int winHeight;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
	GLuint mMatrixId = -1;
	GLuint pMatrixId = -1;
	GLuint colorUniformId = -1;
	GLuint renderModeUniformId = -1;

	GLuint gProgramId;
	int gPos2DLocation;
	int gTex2DLocation;
	void PrintProgramLog(GLuint program);
	bool Initialize(string vertexShaderFile, string fragmentShaderFile);
	Shader *vertexShader;
	Shader *fragmentShader;
	map <string, MeshVbo*> shapes;
	void SetMeshAttribId(MeshVbo * shape);

public:
	/// @brief The function for rendering all drawable object in object list.
	/// @param objList describes the vector list of DrawableObject.
	void Render(vector <DrawableObject*> & objList);
	/// @brief The constructor. Using for setup the camera projection value.
	/// @param w describes the width of window
	/// @param h descrives the height of window
	GLRenderer(int w, int h);
	/// @brief The function using for initialize the shader information
	/// @param vertexShaderFile describes the name of vertex shader file.
	/// @param fragmentShaderFile describes the name of fragment shader file.
	/// @return It will return false if it can't initialize GLEW or OpenGL. return true if it's work normally.
	bool InitGL(string vertexShaderFile, string fragmentShaderFile);
	/// @brief The function for adding the mesh information.
	/// @param name describes the mesh name/key for STL map list.
	/// @param shape describes the Vbo information of the mesh.
	void AddMesh(string name, MeshVbo* shape);
	/// @brief The getter function for the saved mesh Vbo.
	/// @param name describes the name of mesh you want to get.
	/// @return It will return the pointer to the mesh Vbo information.
	MeshVbo * GetMesh(string name);
	/// @brief The function for clear saved mesh information.
	void ClearMesh();

	/// @brief The Destructor. Using for clean up some Gl attribute.
	~GLRenderer();

	/// @brief The function for setup the ortho projection of camera
	/// @param left describe the position at the left of the screen
	/// @param right describe the position at the right of the screen
	/// @param bottom describe the position at the bottom of the screen
	/// @param top describe the position at the top of the screen
	/// @note Pann need to use this function.
	void SetOrthoProjection(float left, float right, float bottom, float top);
	/// @brief The function for setup the window viewport of camera
	/// @param x describe the x-coordinate of bottom left of viewport in pixel.
	/// @param y describe the y-coordinate of bottom left of viewport in pixel.
	/// @param w describe the width of viewport in pixel.
	/// @param h describe the height of viewport in pixel.
	/// @note Pann need to use this function.
	void SetViewPort(int x, int y, int w, int h);
	/// @brief The function for setup the clear color (color that paste over the screen during screen clearing process)
	/// @param r describe the r(rgb) value
	/// @param g describe the g(rgb) value
	/// @param b describe the b(rgb) value
	void SetClearColor(float r, float g, float b);

	/// @brief The getter function for Model attribute of current shader.
	/// @return It will return the model attribute if there is the model matrix in the shader data. return -1 if not.
	GLuint GetModelMatrixAttrId();
	/// @brief The getter function for Projection attribute of current shader.
	/// @return It will return the projection attribute if there is the projection matrix in the shader data. return -1 if not.
	GLuint GetProjectionMatrixAttrId();
	/// @brief The getter function for color uniform of current shader.
	/// @return It will return the color uniform attribute if there is the color uniform in the shader data. return -1 if not.
	GLuint GetColorUniformId();
	/// @brief The getter function for mode uniform of current shader.
	/// @return It will return the mode uniform attribute if there is the mode uniform in the shader data. return -1 if not.
	GLuint GetModeUniformId();

	/// @brief The function for loading texture data
	/// @param path describes the file path of the texture file.
	/// @return It will return the array of integer that store texture name;
	GLuint LoadTexture(string path);
};
