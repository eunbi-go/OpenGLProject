#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

enum class CAMERA_MODE
{
	BACK, TOP, SHAKE, ANI, END
};

class Camera
{
private:
	Camera();
	~Camera();

public:
	void Initialize();

public:
	void Update(float deltaTime);
	void UpdateTexMode(GLuint texProgram);
	void UpdateNormalMode(GLuint program);

	void MoveForward(float speed);
	void MoveHorizontal(float speed);

public:
	void ChangeMode();
	void SetSpeed(float speed) { _speed = speed; }

private:
	glm::vec3 _position = glm::vec3(0.0f, 1.0f, 2.0f);
	glm::vec3 _direction = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 _front = glm::vec3(0.0f, 0.0f, -1.f);
	glm::vec3 _on = glm::vec3(0.0f, -1.0f, 0.f);
	glm::mat4 _view = glm::mat4(1.0f);

	CAMERA_MODE _mode = CAMERA_MODE::BACK;
	float		_speed = 0.f;
	bool		_isUp = false;
	bool		_isCamAni = false;

	GLuint		_program;
	GLuint		_texProgram;

public:
	static Camera* Get_Instance()
	{
		if (!_pInstance)
			_pInstance = new Camera;
		return _pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(_pInstance);
	}

private:
	static Camera* _pInstance;
};

#endif // !__CAMERA_H__