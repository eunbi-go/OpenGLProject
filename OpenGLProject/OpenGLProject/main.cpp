#define _CRT_SECURE_NO_WARNINGS


#include "stdafx.h"
#include "Camera.h"
#include "Cube.h"
#include "MainGame.h"
#include "Player.h"

#include "Timer.h"



MainGame mainGame;
bool isUp = false;
bool isCamAni = false;
void IdleScene();
void Init();
GLvoid Keyboard(unsigned char key, int x, int y);
void MouseInput(int button, int state, int x, int y);

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;
	return buf;
}
GLchar* vertexsource, * fragmentsource;
GLuint vertexshader, fragmentshader;

GLchar* vertexTexSource, * fragmentTexSource;
GLuint vertexTexShader, fragmentTexShader;

void make_vertexShader()
{
	vertexsource = filetobuf("vertexs.glsl");
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	glCompileShader(vertexshader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
		//return false;
	}

	{
		// texture
		vertexTexSource = filetobuf("vertexTexture.glsl");
		vertexTexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexTexShader, 1, (const GLchar**)&vertexTexSource, 0);
		glCompileShader(vertexTexShader);

		GLint result;
		GLchar errorLog[512];
		glGetShaderiv(vertexTexShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(vertexTexShader, 512, NULL, errorLog);
			cerr << "ERROR: vertexTexture shader 컴파일 실패\n" << errorLog << endl;
			//return false;
		}
	}
}

void make_fragmentShader()
{
	fragmentsource = filetobuf("fragments.glsl");
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	glCompileShader(fragmentshader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
		//return false;
	}

	// texture
	{
		fragmentTexSource = filetobuf("fragmentsTexture.glsl");
		fragmentTexShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentTexShader, 1, (const GLchar**)&fragmentTexSource, 0);
		glCompileShader(fragmentTexShader);

		GLint result;
		GLchar errorLog[512];
		glGetShaderiv(fragmentTexShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(fragmentTexShader, 512, NULL, errorLog);
			cerr << "ERROR: fragmentsTexture shader 컴파일 실패\n" << errorLog << endl;
			//return false;
		}
	}
}

void InitBuffer()
{
}

GLuint s_program;
GLuint s_TexProgram;

void InitShader()
{
	make_vertexShader();
	make_fragmentShader();

	s_program = glCreateProgram();
	s_TexProgram = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glAttachShader(s_TexProgram, vertexTexShader);
	glAttachShader(s_TexProgram, fragmentTexShader);
	glLinkProgram(s_program);
	glLinkProgram(s_TexProgram);
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	glDeleteShader(vertexTexShader);
	glDeleteShader(fragmentTexShader);
	glUseProgram(s_program);
}

bool isShake = false;
//ShakeInfo shakeInfo = {};
//
//glm::vec3 _position;
//glm::vec3 _up;


//--- 그리기 콜백 함수
GLvoid drawScene()
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	{
		glUseProgram(s_TexProgram);


		Camera::Get_Instance()->UpdateTexMode(s_TexProgram);


		// project
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 200.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0));
		unsigned int projectLoc = glGetUniformLocation(s_TexProgram, "projectionTransform");
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
	}

	{
		glUseProgram(s_program);

		Camera::Get_Instance()->UpdateNormalMode(s_program);

		// project
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 200.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0));
		{
			unsigned int projectLoc = glGetUniformLocation(s_program, "projectionTransform");
			glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
		}

		// 플레이어 원점 돌아갔을때 카메라 위치 초기화
		if (mainGame.Get_Player() != nullptr && static_cast<Player*>(mainGame.Get_Player())->GetIsRespawn()) {

			Camera::Get_Instance()->Initialize();


			static_cast<Player*>(mainGame.Get_Player())->SetIsRespawn(false);
		}
	}


	mainGame.Render(s_program, s_TexProgram);

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

DWORD dwTime = GetTickCount();

void IdleScene()
{
	if (dwTime + 60 < GetTickCount())
	{
		mainGame.Update();
		mainGame.Late_Update();

		dwTime = GetTickCount();
		
		glutPostRedisplay();	// mainGame.Render();

	}

}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	float speed = 20.f;
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

	if (static_cast<Player*>(mainGame.Get_Player())->GetIsSpeedUp()) speed = 30.f;
	else speed = 20.f;
	speed *= (float)mainGame.Get_DeltaTime();



	switch (key)
	{
	case 'q':
	case 'Q':
		mainGame.Release();
		exit(1);
		break;

	case 'e':
	case 'E':
		Camera::Get_Instance()->ChangeMode();
		break;

		// 아이템 적용 테스트
	case '1':	// 투명화
		static_cast<Player*>(mainGame.Get_Player())->SetItemOn(ITEMTYPE::ALPHA);
		break;

	case '2':	// 스피드업
		static_cast<Player*>(mainGame.Get_Player())->SetItemOn(ITEMTYPE::SPEEDUP);
		break;
	case '3':
		break;

	case '4':
		mainGame.Start_CameraShake();
		break;

	default:
		break;
	}

	InitBuffer();
	glutPostRedisplay();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float posX = (float)(x - (float)800 / 2.0) * (float)(1.0 / (float)(800 / 2.0));
		float posY = -(float)(y - (float)600 / 2.0) * (float)(1.0 / (float)(600 / 2.0));

		if (mainGame.GetCurrentSceneType() == SCENEID::LOGO)
		{
			if (posX >= -0.3f && posX <= 0.3f && posY >= -0.8f && posY <= -0.5f)
			{
				mainGame.ChangeToStage();
			}
		}
	}
}

void main(int argc, char** argv)
{
	// 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGLProject");

	// GLEW 초기화하기
	glewExperimental = GL_TRUE;

	if (glewInit() == GLEW_OK)	Init();

	InitShader();
	InitBuffer();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutIdleFunc(IdleScene);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseInput);
	glutMainLoop();
}

void Init()
{
	mainGame.Initialize();
	Camera::Get_Instance()->Initialize();

	glEnable(GL_DEPTH_TEST);
}
