#include "stdafx.h"
#include "Camera.h"

Camera* Camera::_pInstance = nullptr;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Late_Update()
{
	if (_mode == CAMERA_MODE::TOP)
		UpdateTexMode();
	else if (_mode == CAMERA_MODE::BACK)
		UpdateNormalMode();
}

void Camera::Render(GLuint _program, GLuint _texProgram)
{
}

void Camera::Initialize()
{
}

void Camera::UpdateTexMode()
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 camDir = glm::vec3(0.f);
	if (_isUp)
	{
		camDir = _position + _front + _on;
	}
	else camDir = _position + _front;


	view = glm::lookAt(_position, camDir, _up);
	unsigned int viewLoc = glGetUniformLocation(s_TexProgram, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
}

void Camera::UpdateNormalMode()
{
	//camera.view = glm::mat4(1.0f);


	//glm::vec3 camDir = glm::vec3(0.f);
	//if (isUp)
	//{
	//	camDir = camera.cameraPos + camera.cameraFront + camera.cameraOn;
	//}
	//else camDir = camera.cameraPos + camera.cameraFront;


	//camera.view = glm::lookAt(camera.cameraPos, camDir, camera.cameraUp);
	//unsigned int viewLoc = glGetUniformLocation(s_program, "viewTransform");
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.view[0][0]);
}
