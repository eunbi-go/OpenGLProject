#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

enum class CAMERA_MODE : unsigned char
{
	BACK, TOP, ANI, END
};

struct ShakeInfo
{
	GLfloat lifeTime = 0.f;
	GLfloat runningTime = 0.f;
	GLfloat vibSize = 0.f;
	GLfloat frequency = 0.f;
};

class Camera
{
private:
	Camera();
	~Camera();

public:
	void Initialize();

	void InitShakeInfo();

public:
	void Update(float deltaTime);
	void UpdateTexMode(GLuint texProgram);
	void UpdateNormalMode(GLuint program);


public:
	void ChangeMode();
	void SetSpeed(float speed) { _speed = speed; }
	void SetPos(glm::vec3 pos);
	void SetIsShake(bool isShake) { _isShake = isShake; }

private:
	void Shake(float deltaTime);
	void CameraAnimation(float deltaTime);

private:
	glm::vec3 _position = glm::vec3(0.0f, 1.0f, 2.0f);
	glm::vec3 _direction = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 _front = glm::vec3(0.0f, 0.0f, -1.f);
	glm::vec3 _on = glm::vec3(0.0f, -1.0f, 0.f);
	glm::mat4 _view = glm::mat4(1.0f);

	GLuint		_program = 0;
	GLuint		_texProgram = 0;

	
	CAMERA_MODE _mode = CAMERA_MODE::BACK;
	float		_speed = 0.f;
	bool		_isCamAni = false;

	ShakeInfo	_shakeInfo = {};
	bool		_isShake = false;

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