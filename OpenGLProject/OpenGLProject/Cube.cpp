#include "stdafx.h"
#include "Cube.h"
#include "Timer.h"

#include "ObjectManager.h"


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


Cube::Cube()
{
}

Cube::~Cube()
{
	Release();
}

void Cube::Initialize()
{
	UpdateBuffer();
}

int Cube::Update(float deltaTime)
{
	if (_isDead) return DEATH;

	return ALIVE;
}

void Cube::Late_Update(float deltaTime)
{

}

void Cube::Render(GLuint _program, GLuint _texProgram)
{
	glm::mat4 finalMat = _scale * _trans * _rotation;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(_vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Cube::Release()
{
	SAFE_DELETE(_parent);
}


void Cube::UpdateBuffer()
{
	glGenVertexArrays(1, &_vaoHandle);
	glBindVertexArray(_vaoHandle);

	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];


	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[0]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), cube_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[1]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), _colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glEnableVertexAttribArray(1);


	GLuint indexBufferObjec;
	glGenBuffers(1, &indexBufferObjec);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjec);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
}

void Cube::RenderFinalMatrix(GLuint _program)
{
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(_finalMat));
	glBindVertexArray(_vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Cube::Move()
{
	double time = Timer::Get_Instance()->Get_DeltaTime();
	glm::mat4	playerTrans = static_cast<Cube*>(ObjectManager::Get_Instance()->Get_Player())->Get_Translation();
	glm::vec3	playerPos = glm::vec3(playerTrans[3][0], playerTrans[3][1], playerTrans[3][2]);
	glm::vec3	pos = glm::vec3(_trans[3][0], _trans[3][1], _trans[3][2]);
	glm::vec3	dir = glm::normalize(playerPos - pos);

	switch (_eCurMoveDir)
	{
	case MOVE_FORWARD:
		_trans = glm::translate(_trans, glm::vec3(0.f, 0.0f, _movingSpeed * -time));
		break;

	case MOVE_BACK:
		_trans = glm::translate(_trans, glm::vec3(0.f, 0.0f, _movingSpeed * time));
		break;

	case MOVE_LEFT:
		_trans = glm::translate(_trans, glm::vec3(_movingSpeed * -time, 0.0f, 0.f));
		break;

	case MOVE_RIGHT:
		_trans = glm::translate(_trans, glm::vec3(_movingSpeed * time, 0.0f, 0.f));
		break;

	case MOVE_TO_PLAYER:
		_trans = glm::translate(_trans, glm::vec3(_movingSpeed * dir.x * time, 0.0f, _movingSpeed * dir.z * time));
		break;

	case MOVE_END:
		break;

	default:
		break;
	}
}

void Cube::Move2()
{
	glm::vec3 acc = glm::vec3(0.f, 0.f, 2.f);
	_speed += acc;
}

void Cube::Jump()
{
	_jumpHeight = (float)((_jumpTime * _jumpTime - _jumpPower * _jumpTime) / 5.f);
	_jumpTime += (float)Timer::Get_Instance()->Get_DeltaTime();

	_trans[3][1] = 0.f;
	float y = _jumpHeight * -1.f;
	_trans = glm::translate(_trans, glm::vec3(0.0f, y, 0.0f));

	// Á¡ÇÁ ³¡
	if (_jumpTime > _jumpPower)
	{
		_jumpTime = 0.f;
		_jumpHeight = 0.f;
		_isJump = false;
	}
}

void Cube::SetColor(float x, float y, float z)
{
	for (int i = 0; i < 24; i += 3)
	{
		_colors[i] = x;
		_colors[i + 1] = y;
		_colors[i + 2] = z;
	}
}
