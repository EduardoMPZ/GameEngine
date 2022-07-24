#pragma once

#include "headers.h"
#include "Player.h"
#include "Camera.h"

class Map
{
public:
	std::vector<Object*> Objetos;
	std::vector<Player*> Players;
	glm::vec2* Textures;
	glm::mat4* Matrices;
	glm::vec4* Vertices;
	GLuint* Indices;
	GLuint NumI;
	GLuint Tsize;
	Shader shaderProgramB, shaderProgramO, shaderProgramP;

	//Player
	GLuint PVAO, PVBO, PIBO;

	//Objects
	GLuint VAO, VBO, IBO, TSSBO, MSSBO, OText;

	//background
	GLuint BVAO, BVBO, BIBO, BText;

	Map();
	void ProcessObjects(char const* filename, GLuint Tsize);
	void setBGTS(char const* filename, glm::vec2 scale);
	void ClearScreen(float R, float G, float B, float A);
	void DrawBG(Camera cam, float zoom);
	void DrawO(Camera cam, float zoom);
	void Draw(Player* p, float zoom);
	void PlayerUpdate(float time);
};

