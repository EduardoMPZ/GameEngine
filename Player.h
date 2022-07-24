#pragma once

#include "headers.h"
#include "Shader.h"
#include "Object.h"

class Player
{
public:
	glm::vec2 Position;
	glm::vec2 V = glm::vec2(0.0f);
	glm::vec2 A = glm::vec2(0.0f, -9.8f);
	float altura;
	float largura;

	bool InAir = true;
	GLuint tex;

	Player();
	Player(float altura, float largura, glm::vec2 Position);
	void Inputs(GLFWwindow* window);
	void Update(float time);
	void Colide(Object* Obj);
};
