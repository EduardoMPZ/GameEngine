#include "headers.h"

#include "Map.h"


int main()
{
	//INICIALIZE GLFW WITH OPENGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//CREATE THE WINDOW
	GLFWwindow* mwindow = glfwCreateWindow(1366, 768, "OpenGL", NULL, NULL);
	if (mwindow == NULL)
	{
		std::cout << "Failed to open the main window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//SET THE SPECIFIED GLFW TO USE THE CREATED WINDOW
	glfwMakeContextCurrent(mwindow);

	//LOAD THE GLAD
	gladLoadGL();

	//SET THE VIEWPORT
	glViewport(0, 0, 1366, 768);

	glm::vec4 vertices[] =
	{
		//Position                       //Texture Cordinate
		glm::vec4(-1.0f,  1.0f,  0.0f,  1.0f), glm::vec4(0.0f,  1.0f,  0.0f,  0.0f), // 0
		glm::vec4( 1.0f,  1.0f,  0.0f,  1.0f), glm::vec4(1.0f,  1.0f,  0.0f,  0.0f), // 1
		glm::vec4(-1.0f, -1.0f,  0.0f,  1.0f), glm::vec4(0.0f,  0.0f,  0.0f,  0.0f), // 2
		glm::vec4( 1.0f, -1.0f,  0.0f,  1.0f), glm::vec4(1.0f,  0.0f,  0.0f,  0.0f)  // 3
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		1, 3, 2
	};

	Object ground0(glm::vec2( 50.0f, -10.0f), glm::vec2(50.0f, 5.0f), glm::vec2(0.0f), sizeof(vertices), vertices, sizeof(indices), indices, true);
	Object ground1(glm::vec2(-50.0f, -10.0f), glm::vec2(50.0f, 5.0f), glm::vec2(0.0f), sizeof(vertices), vertices, sizeof(indices), indices, true);
	Object ground2(glm::vec2(-30.0f, -30.0f), glm::vec2(5.0f, 50.0f), glm::vec2(0.0f), sizeof(vertices), vertices, sizeof(indices), indices, true);
	Player p0(64.0f, 32.0f, glm::vec2(0.0f, 100.0f));

	Map map01;

	map01.Objetos.push_back(&ground0);
	map01.Objetos.push_back(&ground1);
	map01.Objetos.push_back(&ground2);
	map01.Players.push_back(&p0);

	map01.ProcessObjects("12.jpg", 2);

	map01.setBGTS("12.jpg", glm::vec2(1000.0f));

	Camera cam0(16, 9, glm::vec3(0.0f, 0.0f, 1.0f));

	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;

	while (!glfwWindowShouldClose(mwindow))
	{
		map01.ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);
		map01.Draw(map01.Players[0], 1.0f);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(mwindow);
		// Take care of all GLFW events
		glfwPollEvents();
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		map01.PlayerUpdate(float(timeDiff));
		map01.Players[0]->Inputs(mwindow);
		if (timeDiff >= 1.0 / 30.0)
		{
			// Creates new title
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);

			// Resets times and counter
			prevTime = crntTime;
			counter = 0;
			std::cout << FPS << std::endl;
			
		}

	}

	//DESTROY THE MAIN WINDOW
	glfwDestroyWindow(mwindow);
	//TERMINATE GLFW
	glfwTerminate();
	return 0;
}