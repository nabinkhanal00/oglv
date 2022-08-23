#include "Angel.hpp"
#include "Line.hpp"
#include <algorithm>
#include "ResourceManager.hpp"
#include "vec3.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <stdexcept>

int Angel::m_width = 720;
int Angel::m_height = 720;
int Angel::m_depth = 100;

Color Angel::m_color = Color(1.0f, 1.0f, 1.0f, 1.0f);

unsigned int Angel::m_ID = 0;
std::vector<oglm::vec3> triangle;

oglm::vec3 calculateNormal(std::vector<oglm::vec3> &points);

void Angel::init(unsigned int width, unsigned int height)
{

	const float vertices[] = {
		-1.0f, -1.0f, 0.0f, // bottom left
		1.0f, -1.0f, 0.0f,	// bottom right
		1.0f, 1.0f, 0.0f,	// top right
		1.0f, 1.0f, 0.0f,	// top right
		-1.0f, 1.0f, 0.0f,	// top left
		-1.0f, -1.0f, 0.0f, // bottom left
	};

	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
						  (void *)0);
	m_ID = VAO;
	m_width = width;
	m_height = height;
	glBindVertexArray(0);
	ResourceManager::LoadShader("shaders/pixel/vertex.glsl",
								"shaders/pixel/fragment.glsl", "pixel");
}
void Angel::enable()
{
	glBindVertexArray(m_ID);
	ResourceManager::GetShader("pixel").Bind();
}

void Angel::disable()
{
	ResourceManager::GetShader("pixel").Unbind();
	glBindVertexArray(0);
}

unsigned int Angel::getWidth() { return m_width; }
void Angel::setWidth(unsigned int width) { m_width = width; }

unsigned int Angel::getHeight() { return m_height; }
void Angel::setHeight(unsigned int height) { m_height = height; }

oglm::vec2i Angel::map(const float &x, const float &y)
{
	int newX = round((x + 1.0f) * m_width / 2);
	int newY = round((y + 1.0f) * m_height / 2);
	return oglm::vec2i(newX, newY);
}
oglm::vec2 Angel::demap(const int &x, const int &y)
{
	float newX = x / (float)m_width * 2 - 1.0f;
	float newY = y / (float)m_height * 2 - 1.0f;
	return oglm::vec2(newX, newY);
}

oglm::vec2 Angel::demap(const oglm::vec2i &point)
{
	float newX = point.x / (float)m_width * 2 - 1.0f;
	float newY = point.y / (float)m_height * 2 - 1.0f;
	return oglm::vec2(newX, newY);
}
oglm::vec3 Angel::demap(const oglm::vec3i &point)
{
	float newX = point.x / (float)m_width * 2 - 1.0f;
	float newY = point.y / (float)m_height * 2 - 1.0f;
	float newZ = point.z / (float)m_depth * 2 - 1.0f;
	return oglm::vec3(newX, newY, newZ);
}

oglm::vec2i Angel::map(const oglm::vec2f &point)
{
	int newX = round((point.x + 1.0f) * m_width / 2);
	int newY = round((point.y + 1.0f) * m_height / 2);
	return oglm::vec2i(newX, newY);
}
oglm::vec3i Angel::map(const oglm::vec3f &point)
{
	int newX = round((point.x + 1.0f) * m_width / 2);
	int newY = round((point.y + 1.0f) * m_height / 2);
	int newZ = round((point.y + 1.0f) * m_depth / 2);
	return oglm::vec3i(newX, newY, newZ);
}

void Angel::putPixel(int x, int y, int thickness, const oglm::vec4 &color)
{
	enable();
	ResourceManager::GetShader("pixel").SetVec4(
		"inColor", glm::vec4(color.x, color.y, color.z, color.w));
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, thickness, thickness);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_SCISSOR_TEST);
	disable();
}
void Angel::putPixel(float x, float y, int thickness, const oglm::vec4 &color)
{
	enable();
	ResourceManager::GetShader("pixel").SetVec4(
		"inColor", glm::vec4(color.x, color.y, color.z, color.w));
	oglm::vec2i point = map(x, y);
	glEnable(GL_SCISSOR_TEST);
	glScissor(point.x, point.y, thickness, thickness);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_SCISSOR_TEST);
	disable();
}

void Angel::drawAxes(oglm::vec4 color, bool octant)
{
	for (float i = -1.0f; i <= 1.0f; i += 0.001f)
	{
		putPixel(0.0f, i, 1, color);
		putPixel(i, 0.0f, 1, color);
	}
}
