#define _CRT_SECURE_NO_WARNINGS


#include "stdafx.h"

#include "Cube.h"
#include "MainGame.h"
#include "Player.h"

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> randomC(0.0, 1.0);
uniform_real_distribution<> randomSpeed(0.001, 0.01);


struct Camera
{
	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 2.0f);
	glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.f);
	glm::mat4 view = glm::mat4(1.0f);
};

MainGame game;
Camera camera;

void IdleScene();
void Init();
GLvoid Keyboard(unsigned char key, int x, int y);

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
}

void InitBuffer()
{
}

GLuint s_program;

void InitShader()
{
	make_vertexShader(); 
	make_fragmentShader();

	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	glUseProgram(s_program);
}

//--- 그리기 콜백 함수
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(s_program);

	// camera
	camera.view = glm::mat4(1.0f);
	camera.view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
	unsigned int viewLoc = glGetUniformLocation(s_program, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.view[0][0]);

	// project
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 200.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0));
	unsigned int projectLoc = glGetUniformLocation(s_program, "projectionTransform");
	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);

	game.Render(s_program);

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

DWORD dwTime = GetTickCount();

void IdleScene()
{
	if (dwTime + 10 < GetTickCount())
	{
		game.Update();
		game.Late_Update();
		dwTime = GetTickCount();

		glutPostRedisplay();

	}

}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	float speed = 3.f;
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
	speed *= game.Get_DeltaTime();

	switch (key)
	{
	case 'W': 
	case 'w':
		static_cast<Cube*>(game.Get_Player())->SetMoveDir(MOVE::MOVE_FORWARD);
		static_cast<Cube*>(game.Get_Player())->Move(MOVE::MOVE_FORWARD);
		camera.cameraPos += camera.cameraFront * speed;
		break;

	case 'S':
	case 's':
		static_cast<Cube*>(game.Get_Player())->SetMoveDir(MOVE::MOVE_BACK);
		static_cast<Cube*>(game.Get_Player())->Move(MOVE::MOVE_BACK);
		camera.cameraPos -= camera.cameraFront * speed;
		break;

	case 'A':
	case 'a':
		static_cast<Cube*>(game.Get_Player())->SetMoveDir(MOVE::MOVE_LEFT);
		static_cast<Cube*>(game.Get_Player())->Move(MOVE::MOVE_LEFT);
		camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, up)) * speed;
		break;

	case 'D':
	case 'd':
		static_cast<Cube*>(game.Get_Player())->SetMoveDir(MOVE::MOVE_RIGHT);
		static_cast<Cube*>(game.Get_Player())->Move(MOVE::MOVE_RIGHT);
		camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, up)) * speed;
		break;

	case 'q':
	case 'Q':
		static_cast<Cube*>(game.Get_Player())->_isJump = true;
		break;

	// 아이템 적용 테스트
	case '1':	// 투명화

		break;

	case '2':	// 스피드업
		static_cast<Player*>(game.Get_Player())->SetItemOn(ITEMTYPE::SPEEDUP);
		break;
	case '3':

		break;

	default:
		break;
	}

	InitBuffer();
	glutPostRedisplay();
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
	glutMainLoop();
}

void Init()
{
	game.Initialize();

	glEnable(GL_DEPTH_TEST);

	{
		//cube.SetPos(glm::vec3(0.0, 0.0, 0));
		//cube.SetScale(glm::vec3(2.f, 2.f, 2.f));
		//cube.SetRotateX(30.f); cube.SetRotateY(-30.f);
	}
}
