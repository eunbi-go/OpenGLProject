#include "stdafx.h"
#include "TexturedRect.h"
#define  STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertexData[] = {
	//--- ��ġ				//--- �븻			//--- �ؽ�ó ��ǥ
	-30.f, -0.5f, 30.f,		0.0, 0.0, 1.0,		0.0, 0.0,
	30.f, -0.5f, 30.f,		0.0, 0.0, 1.0,		1.0, 0.0,
	30.f, -0.5f, -30.f,		0.0, 0.0, 1.0,		1.0, 1.0,

	30.f, -0.5f, -30.f,		0.0, 0.0, 1.0,		1.0, 1.0,
	-30.f, -0.5f, -30.f,		0.0, 0.0, 1.0,		0.0, 1.0,
	-30.f, -0.5f, 30.f,		0.0, 0.0, 1.0,		0.0, 0.0
};
float vertexButtonData[] = {
	//--- ��ġ				//--- �븻			//--- �ؽ�ó ��ǥ
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻�� �Ӽ�
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //--- �ؽ�ó ��ǥ �Ӽ�
	glEnableVertexAttribArray(2);


	// initTexture
	BITMAPINFO* bmp;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// �ؽ�ó �ε� �� ����
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻�� �Ӽ�
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //--- �ؽ�ó ��ǥ �Ӽ�
	glEnableVertexAttribArray(2);


	// initTexture
	BITMAPINFO* bmp;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// �ؽ�ó �ε� �� ����
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
