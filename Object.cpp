#include "Object.h"

Object::Object(glm::vec2 Position, glm::vec2 Scale, glm::vec2 Texture, int Vsize, glm::vec4* Vertices, int Isize, GLuint* Indices, bool tipo)
{
	this->Vertices = Vertices;
	this->Vsize = Vsize;
	this->Indices = Indices;
	this->Isize = Isize;
	this->Position = glm::vec4(Position, 0.0f, 1.0f);
	this->Scale = glm::vec4(Scale, 1.0f, 1.0f);
	this->Texture = Texture;
	this->tipo = tipo;
}

