#include "stdafx.h"
#include "Cube.h"

GLshort cube_indices[] = {
	// Front.
	3, 2, 1, 0,
	// Left.
	0, 3, 7, 4,
	// Bottom.
	4, 0, 1, 5,
	// Right.
	5, 1, 2, 6,
	// Back.
	6, 5, 4, 7,
	// Top.
	7, 6, 2, 3
};

GLfloat cube_vertices[] = {
	-0.2f,	-0.2f,	0.2f,		// 0.
	0.2f,	-0.2f,	0.2f,		// 1.
	0.2f,	0.2f,	0.2f,		// 2.
	-0.2f,	0.2f,	0.2f,		// 3.
	-0.2f,	-0.2f,	-0.2f,	// 4.
	0.2f,	-0.2f,	-0.2f,		// 5.
	0.2f,	0.2f,	-0.2f,		// 6.
	-0.2f,	0.2f,	-0.2f,		// 7.
};

GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.5f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.0f
};

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::Initialize()
{
	UpdateBuffer();
}

int Cube::Update()
{
	return OBJ_NOEVENET;
}

void Cube::Late_Update()
{

}

void Cube::Render(GLuint _program)
{
	glm::mat4 finalMat = scale * trans * rotation;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Cube::Release()
{
}


void Cube::UpdateBuffer()
{
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];


	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[0]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), cube_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[1]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(1);


	GLuint indexBufferObjec;
	glGenBuffers(1, &indexBufferObjec);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjec);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
}

void Cube::Move(MOVE move)
{
	if (_ePreMoveDir != _eCurMoveDir)
	{
		moving = 0.f;
		_ePreMoveDir = _eCurMoveDir;
	}

	switch (move)
	{
	case MOVE_FORWARD:
		moving -= 0.05f;
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, moving));
		break;

	case MOVE_BACK:
		moving += 0.05f;
		trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, moving));
		break;

	case MOVE_LEFT:
		moving -= 0.05f;
		trans = glm::translate(trans, glm::vec3(moving, 0.0f, 0.0f));
		break;

	case MOVE_RIGHT:
		moving += 0.05f;
		trans = glm::translate(trans, glm::vec3(moving, 0.0f, 0.0f));
		break;

	case MOVE_END:
		break;

	default:
		break;
	}
}
