// Include GLFW

#include <iostream>
#include <Ellipse.hpp>

#include "Cube.hpp"
#include <GLFW/glfw3.h>

const unsigned int WIDTH = 1920;
const unsigned int HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow *window, unsigned int width,
                               unsigned int height) {

	Angel::setHeight(height);
	Angel::setWidth(width);
	glViewport(0, 0, width, height);
}

oglm::vec3 at(0.0f, 0.0f, 1.0f);
oglm::vec3 to(0.0f, 0.0f, 0.0f);
oglm::vec3 up(0.0f, 1.0f, 0.0f);

void handleInput(GLFWwindow *window) {
	float speed = 0.09f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		at.y += speed;
		to.y += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		at.y -= speed;
		to.y -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		at.z += speed;
		to.z += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		at.z -= speed;
		to.z -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		at.x -= speed;
		to.x -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		at.x += speed;
		to.x += speed;
	}
}
GLFWwindow *InitWindow() {
	// Initialise GLFW
	if (!glfwInit()) {
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
	    glfwCreateWindow(WIDTH, HEIGHT, "opengl-Red triangle", NULL, NULL);
	if (window == NULL) {
		fprintf(
		    stderr,
		    "Failed to open GLFW window. If you have an Intel GPU, they are "
		    "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Unable to laod GLAD" << std::endl;
	}

	std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return window;
}

int main(void) {
	GLFWwindow *window = InitWindow();
	if (!window)
		return -1;
	Angel::init(WIDTH, HEIGHT);
	// Angel::set_perspective((float)M_PI_2,
	//                        Angel::getWidth() / (float)Angel::getHeight(),
	//                        0.1, 100.0f);
	Line l(0, 0, 1, 1, 10);
	// Cube c(1, 1);
	// c.load();
	// Circle c(0.0f, 0.0f, 0.5f, 4);
	// Ellipse e(0, 0, 0.8f, 0.8f, 4);
	// // Line l(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1);
	// l.show_points();
	// l.show_points();
	// float angle = 4.0f;
	while (glfwWindowShouldClose(window) == false) {
		handleInput(window);
		Angel::current_buffer.clear();

		// Angel::set_view(at, to, up);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//
		// Angel::set_model(oglm::vec3(0.0f, 0.0f, -4.0f),
		//                  oglm::vec3(1.0f, 1.0f, 1.0f), angle += 0.02f,
		//                  oglm::normalize(oglm::vec3(0.0f, 1.0f, 0.0f)));
		//
		// Angel::draw(oglm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		l.animate();
		// e.animate();
		// Angel::set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
		Angel::drawAxes();
		// Angel::set_color(
		//     Color(cos(glfwGetTime()), sin(glfwGetTime()), 1.0f, 1.0f));
		// Angel::set_model(oglm::vec3(1.0f, 0.0f, -2.0f),
		//                  oglm::vec3(.5f, .5f, .5f), angle += 0.02f,
		//                  oglm::normalize(oglm::vec3(0.0f, 1.0f, 0.0f)));
		// Angel::draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}
