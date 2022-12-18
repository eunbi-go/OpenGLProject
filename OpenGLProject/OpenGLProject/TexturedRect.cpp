#include "stdafx.h"
#include "TexturedRect.h"
#define  STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertexData[] = {
	//--- 위치				//--- 노말			//--- 텍스처 좌표
	-30.f, -0.5f, 30.f,		0.0, 0.0, 1.0,		0.0, 0.0,
	30.f, -0.5f, 30.f,		0.0, 0.0, 1.0,		1.0, 0.0,
	30.f, -0.5f, -30.f,		0.0, 0.0, 1.0,		1.0, 1.0,

	30.f, -0.5f, -30.f,		0.0, 0.0, 1.0,		1.0, 1.0,
	-30.f, -0.5f, -30.f,		0.0, 0.0, 1.0,		0.0, 1.0,
	-30.f, -0.5f, 30.f,		0.0, 0.0, 1.0,		0.0, 0.0
};
float vertexButtonData[] = {
	//--- 위치				//--- 노말			//--- 텍스처 좌표
	-0.5f, -0.3f, 0.5f,		0.0, 0.0, 1.0,		0.0, 0.0,
	0.5f, -0.3f, 0.5f,		0.0, 0.0, 1.0,		1.0, 0.0,
	0.5f, 0.3f, 0.5f,		0.0, 0.0, 1.0,		1.0, 1.0,

	0.5f, 0.3f, 0.5f,		0.0, 0.0, 1.0,		1.0, 1.0,
	-0.5f, 0.3f, 0.5f,		0.0, 0.0, 1.0,		0.0, 1.0,
	-0.5f, -0.3f, 0.5f,		0.0, 0.0, 1.0,		0.0, 0.0
};

TexturedRect::TexturedRect()
{
}

TexturedRect::~TexturedRect()
{
}

void TexturedRect::Initialize()
{
	if (_type == TEX_TYPE::LOGO)
		UpdateButtonBuffer();
	else
		UpdateBuffer();
}

int TexturedRect::Update()
{
	return OBJ_NOEVENET;
}

void TexturedRect::Late_Update()
{
}

void TexturedRect::Render(GLuint _program, GLuint _texProgram)
{
	glUseProgram(_texProgram);
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void TexturedRect::Release()
{
}

void TexturedRect::UpdateBuffer()
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
	unsigned char* data = nullptr;
		data = stbi_load("grass.jpg", &width, &height, &nrChannels, 0);
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

void TexturedRect::UpdateButtonBuffer()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexButtonData), vertexButtonData, GL_STATIC_DRAW);
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
	unsigned char* data = nullptr;
		data = stbi_load("start.png", &width, &height, &nrChannels, 0);
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
