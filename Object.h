#pragma once

#include "headers.h"

class Object
{
public:
	glm::vec4* Vertices;
	GLuint* Indices;
	glm::vec4 Position;
	glm::vec4 Scale;
	glm::vec2 Texture;
	int Vsize;
	int Isize;
	bool tipo;

	Object();
	Object(glm::vec2 Position, glm::vec2 Scale, glm::vec2 Texture, int Vsize, glm::vec4* Vertices, int Isize, GLuint* Indices, bool tipo);
};

