#include "Map.h"

Map::Map()
{
	#pragma region ShaderProgram

	shaderProgramB.Inicialize("Vert(default).glsl", "Frag(default).glsl");
	shaderProgramO.Inicialize("Vert(Object).glsl", "Frag(Object).glsl");
	shaderProgramP.Inicialize("Vert(Player).glsl", "Frag(Player).glsl");

	#pragma endregion

	glm::vec4 vertices[] =
	{
		//Position                       //Texture Cordinate
		glm::vec4(-1.0f,  1.0f,  0.0f,  1.0f), glm::vec4(0.0f,  1.0f,  0.0f,  0.0f), // 0
		glm::vec4(1.0f,  1.0f,  0.0f,  1.0f) , glm::vec4(1.0f,  1.0f,  0.0f,  0.0f), // 1
		glm::vec4(-1.0f, -1.0f,  0.0f,  1.0f), glm::vec4(0.0f,  0.0f,  0.0f,  0.0f), // 2
		glm::vec4(1.0f, -1.0f,  0.0f,  1.0f) , glm::vec4(1.0f,  0.0f,  0.0f,  0.0f)  // 3
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		1, 3, 2
	};

	// Generate the VAO, VBO, and EBO with only 1 object each
	glGenVertexArrays(1, &PVAO);
	glGenBuffers(1, &PVBO);
	glGenBuffers(1, &PIBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(PVAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, PVBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PIBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)(sizeof(glm::vec4)));
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Map::ProcessObjects(char const* filename, GLuint Tsize)
{
	#pragma region CreateArrays

	this->Tsize = Tsize;
	int aux0 = 0;
	int aux1 = 0;
	int aux2 = 0;
	int VTsize = 0;
	int ITsize = 0;

	Matrices = (glm::mat4*)malloc(Objetos.size() * sizeof(glm::mat4));
	Textures = (glm::vec2*)malloc(Objetos.size() * sizeof(glm::vec2));

	for (Object* Objeto : Objetos)
	{

		Matrices[aux0] = glm::translate(glm::vec3(Objeto->Position.x, Objeto->Position.y, 0.0f)) * glm::scale(glm::vec3(Objeto->Scale.x, Objeto->Scale.y, 1.0f));
		glm::mat4 teste = glm::translate(glm::vec3(Objeto->Position.x, Objeto->Position.y, 0.0f));
		std::cout << teste[0].x << "," << teste[0].y << "," << teste[0].z << "," << teste[0].w << "\n";
		std::cout << teste[1].x << "," << teste[1].y << "," << teste[1].z << "," << teste[1].w << "\n";
		std::cout << teste[2].x << "," << teste[2].y << "," << teste[2].z << "," << teste[2].w << "\n";
		std::cout << teste[3].x << "," << teste[3].y << "," << teste[3].z << "," << teste[3].w << "\n";

		Textures[aux0] = Objeto->Texture;

		aux0++;

		VTsize += Objeto->Vsize;

		ITsize += Objeto->Isize;

	}

	NumI = ITsize / sizeof(GLuint);

	Vertices = (glm::vec4*)malloc(VTsize);
	Indices = (GLuint*)malloc(ITsize);

	VTsize = 0;

	aux0 = 0;
	aux1 = 0;
	aux2 = 0;

	for (Object* Objeto : Objetos)
	{
		for (int i = 0; i < (Objeto->Vsize / sizeof(glm::vec4)); i++, aux0++)
		{
			if (i % 2 > 0)
			{
				Vertices[aux0] = glm::vec4(Objeto->Vertices[i].x, Objeto->Vertices[i].y, Objeto->Vertices[i].z, aux2);
			}
			else
			{
				Vertices[aux0] = Objeto->Vertices[i];
			}
		}

		for (int i = 0; i < (Objeto->Isize / sizeof(GLuint)); i++, aux1++)
		{
			Indices[aux1] = Objeto->Indices[i] + (VTsize / (2 * sizeof(glm::vec4)));
		}

		VTsize += Objeto->Vsize;
		aux2++;
	}

	#pragma endregion

	#pragma region BuffersCreation

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, VTsize, Vertices, GL_STATIC_DRAW);

	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ITsize, Indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)(sizeof(glm::vec4)));
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &TSSBO);
	glGenBuffers(1, &MSSBO);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, TSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, Objetos.size() * sizeof(glm::vec2), this->Textures, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, TSSBO);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, MSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, Objetos.size() * sizeof(glm::mat4), this->Matrices, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, MSSBO);

	#pragma endregion

	#pragma region ObjectTextures

	glGenTextures(1, &OText);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, OText);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	#pragma endregion
}

void Map::setBGTS(char const* filename, glm::vec2 scale)
{
	#pragma region BMesh

	glm::vec4 vertices[] =
	{
		//Position                       //Texture Cordinate
		glm::vec4(-1.0f,  1.0f,  0.0f,  1.0f) * glm::vec4(scale, 0.0f, 1.0f), glm::vec4(0.0f,  1.0f,  0.0f,  0.0f), // 0
		glm::vec4(1.0f,  1.0f,  0.0f,  1.0f) * glm::vec4(scale, 0.0f, 1.0f), glm::vec4(1.0f,  1.0f,  0.0f,  0.0f), // 1
		glm::vec4(-1.0f, -1.0f,  0.0f,  1.0f) * glm::vec4(scale, 0.0f, 1.0f), glm::vec4(0.0f,  0.0f,  0.0f,  0.0f), // 2
		glm::vec4(1.0f, -1.0f,  0.0f,  1.0f) * glm::vec4(scale, 0.0f, 1.0f), glm::vec4(1.0f,  0.0f,  0.0f,  0.0f)  // 3
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		1, 3, 2
	};

	// Generate the VAO, VBO, and EBO with only 1 object each
	glGenVertexArrays(1, &BVAO);
	glGenBuffers(1, &BVBO);
	glGenBuffers(1, &BIBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(BVAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, BVBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BIBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)(sizeof(glm::vec4)));
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	#pragma endregion

	#pragma region CreateTexture

	glGenTextures(1, &BText);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BText);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	#pragma endregion
}

void Map::ClearScreen(float R, float G, float B, float A)
{
	glClearColor(R, G, B, A);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Map::DrawBG(Camera cam, float zoom)
{
	shaderProgramB.Activate();

	glUniform1i(glGetUniformLocation(shaderProgramB.ID, "BackGround"), BText - 1);

	cam.Matrix(zoom * 250.0f, 0.1f, 100.0f, shaderProgramB, "CamM");

	shaderProgramB.Activate();

	glBindVertexArray(BVAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Map::DrawO(Camera cam, float zoom)
{
	shaderProgramO.Activate();

	glUniform1i(glGetUniformLocation(shaderProgramO.ID, "textsize"), Tsize);

	cam.Matrix(zoom * 250.0f, 0.1f, 100.0f, shaderProgramO, "CamM");

	glBindVertexArray(VAO);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, TSSBO);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, MSSBO);

	glDrawElements(GL_TRIANGLES, NumI, GL_UNSIGNED_INT, 0);
}

void Map::PlayerUpdate(float time)
{
	for (Player* p : Players)
	{
		p->Update(time);

		for (Object* Objeto : Objetos)
		{
			p->Colide(Objeto);
		}
	}
}

void Map::Draw(Player* p, float zoom)
{
	Camera cam(16, 9, glm::vec3(0.0f, 0.0f, 1.0f));
	DrawBG(cam, zoom);
	DrawO(cam, zoom);

	shaderProgramP.Activate();
	
	glm::mat4 Model = glm::translate(glm::vec3(p->Position, 0.0f)) * glm::scale(glm::vec3(p->largura/2, p->altura/2, 1.0f));
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramP.ID, "Model"), 1, 0, glm::value_ptr(Model));
	
	cam.Matrix(zoom * 250.0f, 0.1f, 100.0f, shaderProgramP, "CamM");
	
	shaderProgramP.Activate();
	
	glBindVertexArray(PVAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}