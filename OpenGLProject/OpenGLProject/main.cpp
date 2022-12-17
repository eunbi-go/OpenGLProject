#define _CRT_SECURE_NO_WARNINGS
#define  STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "stdafx.h"

#include "Cube.h"
#include "MainGame.h"
#include "Player.h"




struct Camera
{
	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 2.0f);
	glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.f);
	glm::vec3 cameraOn = glm::vec3(0.0f, -1.0f, 0.f);
	glm::mat4 view = glm::mat4(1.0f);
};

MainGame game;
Camera camera;
bool isUp = false;
bool isCamAni = false;
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

float vertexData[] = {
	//--- 위치				//--- 노말			//--- 텍스처 좌표
	-20.f, -0.5f, 20.f,		0.0, 0.0, 1.0,		0.0, 0.0,
	20.f, -0.5f, 20.f,		0.0, 0.0, 1.0,		1.0, 0.0,
	20.f, -0.5f, -20.f,		0.0, 0.0, 1.0,		1.0, 1.0,

	20.f, -0.5f, -20.f,		0.0, 0.0, 1.0,		1.0, 1.0,
	-20.f, -0.5f, -20.f,		0.0, 0.0, 1.0,		0.0, 1.0,
	-20.f, -0.5f, 20.f,		0.0, 0.0, 1.0,		0.0, 0.0
};

unsigned int VBO, VAO;
unsigned int texture;

void InitBuffer()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //--- 위치 속성
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //--- 노말값 속성
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //--- 텍스처 좌표 속성
	glEnableVertexAttribArray(2);


	// initTexture
	BITMAPINFO* bmp;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 텍스처 로드 및 생성
	int width, height, nrChannels;
	unsigned char* data = stbi_load("grass.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
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

//--- 그리기 콜백 함수
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	{
		glUseProgram(s_TexProgram);

		glm::mat4 view = glm::mat4(1.0f);
		glm::vec3 camDir = glm::vec3(0.f);
		if (isUp)
		{
			camDir = camera.cameraPos + camera.cameraFront + camera.cameraOn;
		}
		else camDir = camera.cameraPos + camera.cameraFront;


		view = glm::lookAt(camera.cameraPos, camDir, camera.cameraUp);
		unsigned int viewLoc = glGetUniformLocation(s_TexProgram, "viewTransform");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		// project
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 200.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0));
		unsigned int projectLoc = glGetUniformLocation(s_TexProgram, "projectionTransform");
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);


		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
	glUseProgram(s_program);

	// camera
	camera.view = glm::mat4(1.0f);
	
	
	glm::vec3 camDir = glm::vec3(0.f);
	if (isUp)
	{
		//camera.cameraPos.y = 2.f;
		camDir = camera.cameraPos + camera.cameraFront + camera.cameraOn;
	}
	else camDir = camera.cameraPos + camera.cameraFront;


	camera.view = glm::lookAt(camera.cameraPos, camDir, camera.cameraUp);
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
float camSpeed = 0.5f;
void IdleScene()
{
	if (dwTime + 40 < GetTickCount())
	{
		game.Update();
		game.Late_Update();

		if (isCamAni)
		{
			if (isUp && camera.cameraPos.y <= 2.f)
			{
				camera.cameraPos.y += game.Get_DeltaTime() * camSpeed;
			}
			else if (!isUp && camera.cameraPos.y >= 1.f)
			{
				camera.cameraPos.y -= game.Get_DeltaTime() * camSpeed;
			}
			else isCamAni = false;
		}

		dwTime = GetTickCount();

		glutPostRedisplay();

	}

}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	float speed = 20.f;
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
	speed *= game.Get_DeltaTime();

	switch (key)
	{
	case 'W': 
	case 'w':
		static_cast<Cube*>(game.Get_Player())->SetMoveDir(MOVE::MOVE_FORWARD);
		static_cast<Cube*>(game.Get_Player())->Move();
		static_cast<Player*>(game.Get_Player())->_isMoveStop = false;
		camera.cameraPos += camera.cameraFront * speed;
		break;

	case 'S':
	case 's':
		static_cast<Cube*>(game.Get_Player())->SetMoveDir(MOVE::MOVE_BACK);
		static_cast<Cube*>(game.Get_Player())->Move();
		static_cast<Player*>(game.Get_Player())->_isMoveStop = false;
		camera.cameraPos -= camera.cameraFront * speed;
		break;

	case 'A':
	case 'a':
		static_cast<Cube*>(game.Get_Player())->SetMoveDir(MOVE::MOVE_LEFT);
		static_cast<Cube*>(game.Get_Player())->Move();
		static_cast<Player*>(game.Get_Player())->_isMoveStop = false;
		camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, up)) * speed;
		break;

	case 'D':
	case 'd':
		static_cast<Cube*>(game.Get_Player())->SetMoveDir(MOVE::MOVE_RIGHT);
		static_cast<Cube*>(game.Get_Player())->Move();
		static_cast<Player*>(game.Get_Player())->_isMoveStop = false;
		camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, up)) * speed;
		break;

	case 'q':
	case 'Q':
		static_cast<Cube*>(game.Get_Player())->_isJump = true;
		break;

	case 'e':
	case 'E':
		isUp = !isUp;
		isCamAni = true;
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
}
