
#include "MeshVbo.h"


MeshVbo::MeshVbo()
{
}

void MeshVbo::LoadQuadData()
{
	GLfloat vertexData[] =
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	GLfloat texData[] =
	{
		0.5f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.5f, 1.0f
	};

	glGenBuffers(1, &posVboId);
	glBindBuffer(GL_ARRAY_BUFFER, posVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &texVboId);
	glBindBuffer(GL_ARRAY_BUFFER, texVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texData), texData, GL_STATIC_DRAW);
}

void MeshVbo::BindVertexAndTextureData()
{
	if (posAttribId != -1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, posVboId);
		glVertexAttribPointer(posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}

	if (texAttribId != -1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, texVboId);
		glVertexAttribPointer(texAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
}

GLuint MeshVbo::GetPosId()
{
	return this->posVboId;
}

GLuint MeshVbo::GetTexId()
{
	return this->texVboId;
}

void MeshVbo::SetAttribId(GLuint posId, GLuint texId)
{
	this->posAttribId = posId;
	this->texAttribId = texId;
}
