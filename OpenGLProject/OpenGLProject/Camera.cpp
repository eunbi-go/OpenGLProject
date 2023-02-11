#include "stdafx.h"
#include "Camera.h"

Camera* Camera::_pInstance = nullptr;

Camera::Camera()
{
	_speed = 0.5f;
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	_position = glm::vec3(0.0f, 1.0f, 2.0f);
	_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);
	_front = glm::vec3(0.0f, 0.0f, -1.f);
	_on = glm::vec3(0.0f, -1.0f, 0.f);
	_view = glm::mat4(1.0f);

	_isUp = false;
	_isCamAni = false;
}

void Camera::Update(float deltaTime)
{
	if (_isCamAni)
	{
		if (_isUp && _position.y <= 2.f)
		{
			_position.y += (GLfloat)(deltaTime * _speed);
		}
		else if (!_isUp && _position.y >= 1.f)
		{
			_position.y -= (GLfloat)(deltaTime * _speed);
		}
		else _isCamAni = false;
	}
}

void Camera::UpdateTexMode(GLuint texProgram)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 camDir = glm::vec3(0.f);
	if (_isUp)
	{
		camDir = _position + _front + _on;
	}
	else camDir = _position + _front;


	view = glm::lookAt(_position, camDir, _up);
	unsigned int viewLoc = glGetUniformLocation(texProgram, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
}

void Camera::UpdateNormalMode(GLuint program)
{
	_view = glm::mat4(1.0f);


	glm::vec3 camDir = glm::vec3(0.f);
	if (_isUp)
	{
		camDir = _position + _front + _on;
	}
	else camDir = _position + _front;


	_view = glm::lookAt(_position, camDir, _up);
	unsigned int viewLoc = glGetUniformLocation(program, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &_view[0][0]);
}

void Camera::MoveForward(float speed)
{
	_position += (_front * speed);
}

void Camera::MoveHorizontal(float speed)
{
	_position += glm::normalize(glm::cross(_front, _up)) * speed;
}

void Camera::ChangeMode()
{
	_isCamAni = true;
	_isUp = !_isUp;

	if (_mode == CAMERA_MODE::BACK)
	{
		_mode = CAMERA_MODE::TOP;
	}
	else if (_mode == CAMERA_MODE::TOP)
	{
		_mode = CAMERA_MODE::BACK;
	}
}
