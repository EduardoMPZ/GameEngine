#include "Player.h"

Player::Player(float altura, float largura, glm::vec2 Position)
{
	this->altura = altura;
	this->largura = largura;
	this->Position = Position;
}

void Player::Inputs(GLFWwindow* window)
{
	if (!InAir)
	{
		A =  glm::vec2(-V.x * 5, A.y);
	}

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		A = glm::vec2(-10.0f, A.y);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		A = glm::vec2(10.0f, A.y);
	}

	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && (!InAir))
	{
		V = glm::vec2(V.x, 20.0f);
		InAir = true;
	}
}

void Player::Update(float time)
{
	//atalizar status
	V += (A * time);
	Position += (V * time);

	//se estpa no ar
	if (abs(V.y) > 1.0f)
	{
		InAir = true;
	}

	//velocidade maxima
	if (V.x > 25.0f)
	{
		V.x = 25.0f;
	}
	if (V.x < -25.0f)
	{
		V.x = -25.0f;
	}
}

void Player::Colide(Object* Obj)
{
	if (Obj->tipo)
	{
		float LTRy = (altura / 2.0f) + (Obj->Vertices[0].y * Obj->Scale.y);
		float LTRx = (largura / 2.0f) + (Obj->Vertices[3].x * Obj->Scale.x);

		float RTRy = Position.y - Obj->Position.y;
		float RTRx = Position.x - Obj->Position.x;

		float MRTRy = abs(RTRy);
		float MRTRx = abs(RTRx);

		float factory = RTRy / MRTRy;
		float factorx = RTRx / MRTRx;

		if (MRTRy < LTRy && MRTRx < LTRx)
		{
			float dify = LTRy - MRTRy;
			float difx = LTRx - MRTRx;
			if (dify < difx)
			{
				Position.y += dify * factory;
				V.y = 0;
				InAir = false;
			}
			else
			{
				if (dify < 0.05 * altura && RTRy > 0.0f)
				{
					Position.y += dify * factory;
					V.y = 0;
					InAir = false;
				}
				else
				{
					Position.x += difx * factorx;
					V.x = 0;
				}
					
			}
		}
	}
	else
	{

	}
}
