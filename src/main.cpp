// Include GLFW

#include <iostream>
#include <Ellipse.hpp>
#include <thread>

#include "Sphere.hpp"
#include "Cube.hpp"
#include "Circle.hpp"
#include <GLFW/glfw3.h>

unsigned int WIDTH = 1000;
unsigned int HEIGHT = 1000;

int current = 1;

void framebuffer_size_callback(GLFWwindow *window, unsigned int width,
                               unsigned int height) {

	Angel::setHeight(height);
	Angel::setWidth(width);
	glViewport(0, 0, width, height);
}

float cameraSpeed = 0.1;
oglm::vec3 &at = Angel::camPos;
oglm::vec3 &to = Angel::camFocus;
oglm::vec3 &up = Angel::camUp;
static void cursorPositionCallback(GLFWwindow *window, double xpos,
                                   double ypos) {
	float x = xpos / WIDTH - 0.5;
	float y = -ypos / HEIGHT + 0.5;
	to += oglm::vec3(x, y, 0);
	glfwSetCursorPos(window, WIDTH / 2.0f, HEIGHT / 2.0f);
}
static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
	at += oglm::vec3(0, 0, -cameraSpeed * yoffset);
	to += oglm::vec3(0, 0, -cameraSpeed * 5 * yoffset);
}

void handleInput(GLFWwindow *window) {
	oglm::vec3 &at = Angel::camPos;
	oglm::vec3 &to = Angel::camFocus;
	oglm::vec3 &up = Angel::camUp;
	float speed = 0.01f;
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
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		current = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		current = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		current = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		current = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		current = 5;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		current = 6;
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
		current = 7;
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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Unable to laod GLAD" << std::endl;
	}

	std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPosCallback(window, cursorPositionCallback);

	return window;
}

int main() {
	GLFWwindow *window = InitWindow();
	if (!window)
		return -1;
	Angel::init(WIDTH, HEIGHT);

	std::vector<Sphere> spheres;
	// position, radius, surface color, reflectivity, transparency, emission
	// color
	spheres.push_back(Sphere(Vec3f(0.0, -10004, -20), 10000,
	                         Vec3f(0.20, 0.20, 0.20), 0, 0.0));
	spheres.push_back(
	    Sphere(Vec3f(0.0, 0, -20), 4, Vec3f(1.00, 0.32, 0.36), 1, 0.5));
	spheres.push_back(
	    Sphere(Vec3f(5.0, -1, -15), 2, Vec3f(0.90, 0.76, 0.46), 1, 0.0));
	spheres.push_back(
	    Sphere(Vec3f(5.0, 0, -25), 3, Vec3f(0.65, 0.77, 0.97), 1, 0.0));
	spheres.push_back(
	    Sphere(Vec3f(-5.5, 0, -15), 3, Vec3f(0.90, 0.90, 0.90), 1, 0.0));
	// light
	spheres.push_back(Sphere(Vec3f(0.0, 20, -30), 3, Vec3f(0.00, 0.00, 0.00), 0,
	                         0.0, Vec3f(3)));

	Vec3f **pixels;
	pixels = new Vec3f *[WIDTH];
	for (int i = 0; i < WIDTH; i++) {
		pixels[i] = new Vec3f[HEIGHT];
	}
	std::thread fc(fillColor, spheres, WIDTH, HEIGHT, pixels);

	Angel::set_perspective((float)M_PI_2,
	                       Angel::getWidth() / (float)Angel::getHeight(), 0.1,
	                       100.0f);
	Line l(-0.5, -0.3, 1, 0.8, 10);

	Cube clippingCube(1, 1);
	clippingCube.load(true);
	clippingCube.set_model(oglm::vec3(0.0f, 0.0f, -2.0f),
	                       oglm::vec3(1.0f, 1.0f, 1.0f), 0.0f,
	                       oglm::normalize(oglm::vec3(0.0f, 1.0f, 0.0f)));
	Cube backfaceCube(1, 1);
	backfaceCube.load(false);
	backfaceCube.set_model(oglm::vec3(0.0f, 0.0f, -2.0f),
	                       oglm::vec3(1.0f, 1.0f, 1.0f), 0.0f,
	                       oglm::normalize(oglm::vec3(0.0f, 1.0f, 0.0f)));

	Cube lightSource(1, 1);
	lightSource.load(false);

	Cube cubeObject(1, 1);
	cubeObject.load(false);
	cubeObject.set_model(oglm::vec3(0.0f, 0.0f, -2.0f),
	                     oglm::vec3(1.0f, 1.0f, 1.0f), 0.0f,
	                     oglm::normalize(oglm::vec3(0.0f, 1.0f, 0.0f)));

	Circle circle(WIDTH / 2, HEIGHT / 2, 400, 10);
	Ellipse ellipse(static_cast<int>(WIDTH / 2), static_cast<int>(HEIGHT / 2),
	                400, 100, 10);
	float angle = 4.0f;
	while (glfwWindowShouldClose(window) == false) {
		handleInput(window);
		Angel::current_buffer.clear();
		Angel::set_view(at, to, up);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		oglm::vec3 lightSourcePos(4 * cos(glfwGetTime()), 0.0f,
		                          4 * sin(glfwGetTime()));
		lightSource.set_model(lightSourcePos, oglm::vec3(0.2f, 0.2f, 0.2f),
		                      0.0f,
		                      oglm::normalize(oglm::vec3(0.0f, 1.0f, 0.0f)));
		if (current == 1) {
			Angel::drawAxes();
			l.animate();

		} else if (current == 2) {
			Angel::drawAxes();
			circle.animate();

		} else if (current == 3) {
			Angel::drawAxes();
			ellipse.animate();
		} else if (current == 4) {
			clippingCube.draw(false, false, oglm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		} else if (current == 5) {
			backfaceCube.draw(true, false, oglm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		} else if (current == 6) {
			lightSource.draw(false, false, oglm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			cubeObject.draw(false, true, oglm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
			                lightSourcePos, oglm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		} else if (current == 7) {
			for (int i = 0; i < WIDTH; i++) {
				for (int j = 0; j < HEIGHT; j++) {
					Vec3f color = pixels[i][HEIGHT - j - 1];
					Angel::putPixel(
					    i, j, 1, oglm::vec4(color.x, color.y, color.z, 1.0f));
				}
			}
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	if (fc.joinable()) {
		fc.join();
	}

	glfwTerminate();

	return 0;
}
