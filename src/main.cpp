// Include GLFW

#include <Ellipse.hpp>
#include <iostream>
#include <thread>

#include "Context.hpp"
#include "Defines.hpp"

#include "Circle.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

const char *glsl_version = "#version 130";
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
	// glfwSetCursorPosCallback(window, cursorPositionCallback);

	glfwSetScrollCallback(window, scrollCallback);
	return window;
}

int main()
{
	GLFWwindow *window = InitWindow();
	if (!window)
		return -1;
	Angel::init(Context::width, Context::height);

	// Initialize ImGUI
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	bool showLineWindow = true;
	// our state
	// line
	float x0{0}, y0{0}, x1{0.8}, y1{0.9};

	// circle
	float circleCenterX{float(Context::width) / 2};
	float circleCenterY{float(Context::height) / 2};
	float circleRadius{400};
        bool startCircleDrawing = true;
        bool drawCircle = true;
        bool animateCircle = false;

        // ellipse
        float ellipseCenterX{float(Context::width) / 2};
        float ellipseCenterY{float(Context::height) / 2};
        float ellipseMajor{300};
        float ellipseMinor{200};
        bool startEllipseDrawing = true;
        bool drawEllipse = true;
        bool animateEllipse = false;

        std::vector<Line> Lines;
        Cube c;
        while (glfwWindowShouldClose(window) == false) {
            handleInput(window);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // IMGUI
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (current == 1) {
                ImGui::Begin(
                    "Line window",
                    &showLineWindow); // Pass a pointer to our bool variable
                ImGui::InputFloat("x0", &x0, 0.01, 2, "%.2f", 0);
                ImGui::InputFloat("y0", &y0, 0.01, 2, "%.2f", 0);
                ImGui::InputFloat("x1", &x1, 0.01, 2, "%.2f", 0);
                ImGui::InputFloat("y1", &y1, 0.01, 2, "%.2f", 0);
                if (x0 < -1.0f)
                    x0 = -1.0f;
                if (y0 < -1.0f)
                    y0 = -1.0f;
                if (y1 < -1.0f)
                    y1 = -1.0f;
                if (x1 < -1.0f)
                    x1 = -1.0f;
                if (x0 > 1.0f)
                    x0 = 1.0f;
                if (y0 > 1.0f)
                    y0 = 1.0f;
                if (y1 > 1.0f)
                    y1 = 1.0f;
                if (x1 > 1.0f)
                    x1 = 1.0f;
                if (ImGui::Button("New line")) {
                    Lines.push_back(Line(x0, y0, x1, y1, 10));
                }
                int c = 0;
                for (auto &line : Lines) {
                    c++;
                    std::string tmp = "Line" + std::to_string(c);
                    char const *num_char = tmp.c_str();
                    ImGui::Begin(
                        num_char,
                        &showLineWindow); // Pass a pointer to our bool
                                          // variable (the window will have
                                          // a closing button that will
                                          // clear the bool when clicked)

                    ImGui::ColorEdit3("color", line.color);
                    if (ImGui::Button("Delete")) {
                        Lines.erase(Lines.begin() + (c - 1));
                    }
                    if (ImGui::Button("Stop")) {
                        line.count = 0;
                        line.i = 0;
                        line.stuck = 0;
                        line.startLineDrawing = false;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Start")) {
                        line.frameCount = 60;
                        line.startLineDrawing = true;
                        line.lineDraw = true;
                        line.lineAnimate = false;
                    }
                    if (line.startLineDrawing) {
                        Angel::drawAxes();
                        if (ImGui::Button("Animate")) {
                            line.stuck = 0;
                            line.lineDraw = false;
                            line.lineAnimate = true;
                        }
                        ImGui::SameLine();
                        ImGui::SameLine();
                        if (ImGui::Button("Draw")) {
                            line.count = 0;
                            line.i = 0;
                            line.stuck = 0;
                            line.lineDraw = true;
                            line.lineAnimate = false;
                        }
                        if (line.lineDraw) {
                            line.draw(oglm::vec4(line.color[0], line.color[1],
                                                 line.color[2], line.color[3]));
                        }
                        if (line.lineAnimate) {
                            if (ImGui::Button("Pause Animation")) {
                                line.frameCount = 1000000;
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("start Animation")) {
                                line.frameCount = 60;
                            }
                            line.animate();
                        }
                    }
                    ImGui::End();
                }
                ImGui::End();
            } else if (current == 2) {
                ImGui::Begin(
                    "circle window"); // Pass a pointer to our bool variable
                ImGui::InputFloat("x0", &circleCenterX, 5, 2, "%.2f", 0);
                ImGui::InputFloat("y0", &circleCenterY, 5, 2, "%.2f", 0);
                ImGui::InputFloat("radius", &circleRadius, 5, 2, "%.2f", 0);
                Circle circle(circleCenterX, circleCenterY, circleRadius, 10);
                Angel::drawAxes();
                if (ImGui::Button("Stop")) {
                    Circle::count = 0;
                    Circle::i = 0;
                    Circle::stuck = 0;
                    startCircleDrawing = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Start")) {
                    Circle::frameCount = 60;
                    startCircleDrawing = true;
                }
                if (startCircleDrawing) {
                    if (ImGui::Button("Animate")) {
                        Circle::frameCount = 60;
                        animateCircle = true;
                        drawCircle = false;
                    }
                    if (ImGui::Button("Draw")) {
                        Circle::frameCount = 60;
                        animateCircle = false;
                        drawCircle = true;
                    }
                    if (drawCircle) {
                        circle.draw();
                    }
                    if (animateCircle) {
                        if (ImGui::Button("Pause Animation")) {
                            Circle::frameCount = 1000000;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("start Animation")) {
                            Circle::frameCount = 60;
                        }
                        circle.animate();
                    }
                }
                ImGui::End();
            } else if (current == 3) {
                ImGui::Begin(
                    "circle window"); // Pass a pointer to our bool variable
                ImGui::InputFloat("x0", &ellipseCenterX, 5, 2, "%.2f", 0);
                ImGui::InputFloat("y0", &ellipseCenterY, 5, 2, "%.2f", 0);
                ImGui::InputFloat("a", &ellipseMajor, 5, 2, "%.2f", 0);
                ImGui::InputFloat("b", &ellipseMinor, 5, 2, "%.2f", 0);
                Ellipse e(ellipseCenterX, ellipseCenterY, ellipseMajor,
                          ellipseMinor, 10);
                Angel::drawAxes();
                if (ImGui::Button("Stop")) {
                    Ellipse::count = 0;
                    Ellipse::i = 0;
                    Ellipse::stuck = 0;
                    startEllipseDrawing = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Start")) {
                    Ellipse::frameCount = 60;
                    startEllipseDrawing = true;
                }
                if (startEllipseDrawing) {
                    if (ImGui::Button("Animate")) {
                        Ellipse::frameCount = 60;
                        animateEllipse = true;
                        drawEllipse = false;
                    }
                    if (ImGui::Button("Draw")) {
                        Ellipse::frameCount = 60;
                        animateEllipse = false;
                        drawEllipse = true;
                    }
                    if (drawEllipse) {
                        e.draw();
                    }
                    if (animateEllipse) {
                        if (ImGui::Button("Pause Animation")) {
                            Ellipse::frameCount = 1000000;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("start Animation")) {
                            Ellipse::frameCount = 60;
                        }
                        e.animate();
                    }
                }
                ImGui::End();
            } else {
                c.draw();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();

        return 0;
}
