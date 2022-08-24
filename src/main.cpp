// Include GLFW

#include <iostream>
#include <Ellipse.hpp>
#include <thread>
#include "Context.hpp"
#include "Defines.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "Cube.hpp"
#include <GLFW/glfw3.h>

// unsigned int Context::width = 1000;
// unsigned int Context::height = 1000;

int current = 1;
bool firstMouse = true;
void framebuffer_size_callback(GLFWwindow *window, unsigned int width,
							   unsigned int height)
{

	Angel::setHeight(height);
	Angel::setWidth(width);
	glViewport(0, 0, width, height);
}

float lastX = Context::width / 2;
float lastY = Context::height / 2;
static void cursorPositionCallback(GLFWwindow *window, double xposIn,
								   double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	Context::cam.ProcessMouseMovement(xoffset, yoffset);
}
static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	Context::cam.ProcessMouseScroll(yoffset);
}
void processEvents()
{
}

void handleInput(GLFWwindow *window)
{
	float deltaTime = 0.001;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Context::cam.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Context::cam.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Context::cam.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Context::cam.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		current = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		current = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		current = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		current = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		current = 5;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		current = 6;
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		current = 7;
	}
}
GLFWwindow *InitWindow()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return nullptr;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
				   GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSwapInterval(1);

	// Open a window and create its OpenGL context
	GLFWwindow *window =
		glfwCreateWindow(Context::width, Context::height, "opengl-Red triangle", NULL, NULL);
	if (window == NULL)
	{
		fprintf(
			stderr,
			"Failed to open GLFW window. If you have an Intel GPU, they are "
			"not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Unable to laod GLAD" << std::endl;
	}

	std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPosCallback(window, cursorPositionCallback);

	glEnable(GL_DEPTH_TEST);

	return window;
}

int main()
{
	GLFWwindow *window = InitWindow();
	if (!window)
		return -1;
	Angel::init(Context::width, Context::height);

	Line l(-0.5, -0.3, 1, 0.8, 10);

	Circle circle(Context::width / 2, Context::height / 2, 400, 10);
	// Ellipse ellipse(static_cast<int>(Context::width / 2), static_cast<int>(Context::height / 2),
	//                 400, 100, 10);
	float angle = 4.0f;

	Cube c;
	while (glfwWindowShouldClose(window) == false)
	{
		handleInput(window);
		processEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (current == 1)
		{
			Angel::drawAxes();
			l.animate();
		}
		else if (current == 2)
		{
			Angel::drawAxes();
			circle.animate();
		}
		else if (current == 3)
		{
			Angel::drawAxes();
			// ellipse.animate();
		}
		else
		{
			c.draw();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
