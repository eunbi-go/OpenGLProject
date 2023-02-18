#include "stdafx.h"
#include "Camera.h"
#include "Timer.h"

Camera* Camera::_pInstance = nullptr;

Camera::Camera()
{
	//_speed = 0.5f;
	_speed = 3.f;
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

	_isCamAni = false;

	InitShakeInfo();
}

void Camera::InitShakeInfo()
{
	_shakeInfo.vibSize = 0.7f;
	_shakeInfo.frequency = 52.f;
	_shakeInfo.runningTime = 1.0f;
	_shakeInfo.lifeTime = 0.f;

	_isShake = false;
}

void Camera::Update(float deltaTime)
{
	if (_isShake)
	{
		Shake(deltaTime);
	}

	if (_isCamAni)
	{
		CameraAnimation(deltaTime);
	}
}

void Camera::UpdateTexMode(GLuint texProgram)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 camDir = glm::vec3(0.f);

	switch (_mode)
	{
	case CAMERA_MODE::BACK:
		camDir = _position + _front;
		break;

	case CAMERA_MODE::TOP:
		camDir = _position + _front + _on;
		break;
	}


	view = glm::lookAt(_position, camDir, _up);
	unsigned int viewLoc = glGetUniformLocation(texProgram, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
}

void Camera::UpdateNormalMode(GLuint program)
{
	_view = glm::mat4(1.0f);
	glm::vec3 camDir = glm::vec3(0.f);

	switch (_mode)
	{
	case CAMERA_MODE::BACK:
		camDir = _position + _front;
		break;

	case CAMERA_MODE::TOP:
		camDir = _position + _front + _on;
		break;
	}


	_view = glm::lookAt(_position, camDir, _up);
	unsigned int viewLoc = glGetUniformLocation(program, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &_view[0][0]);
}

void Camera::ChangeMode()
{
	_isCamAni = true;

	if (_mode == CAMERA_MODE::BACK)
	{
		_mode = CAMERA_MODE::TOP;
	}
	else if (_mode == CAMERA_MODE::TOP)
	{
		_mode = CAMERA_MODE::BACK;
	}
}

void Camera::SetPos(glm::vec3 pos)
{
	_position.x = pos.x;
	_position.z = pos.z + 3.f;
}

void Camera::Shake(float deltaTime)
{
	if (_shakeInfo.runningTime < _shakeInfo.lifeTime || _shakeInfo.vibSize < 0)
	{
		// Finish
		InitShakeInfo();
	}
	else
	{
		// Shaking
		_shakeInfo.lifeTime += deltaTime;
		_shakeInfo.vibSize -= deltaTime;
		_position += (_up * sinf(_shakeInfo.lifeTime * _shakeInfo.frequency) * _shakeInfo.vibSize);
	}
}

void Camera::CameraAnimation(float deltaTime)
{
	if (_mode == CAMERA_MODE::TOP && _position.y <= 2.f)
	{
		_position.y += (deltaTime * _speed);
	}
	else if (_mode == CAMERA_MODE::BACK && _position.y >= 1.f)
	{
		_position.y -= (deltaTime * _speed);
	}
	else _isCamAni = false;
}
