#pragma once
#include "headers.h"

std::string ReadFile(const char* filePath);

class Shader
{
public:
	GLuint ID;
	Shader();
	Shader(const char* vertPath, const char* fragPath);

	void Inicialize(const char* vertPath, const char* fragPath);
	void Activate();
	void Delete();
};

