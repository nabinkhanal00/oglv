#include "Angel.hpp"
#include "Line.hpp"
#include "ResourceManager.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

int Angel::m_width = 1280;
int Angel::m_height = 720;

glm::mat4 Angel::view = {};
glm::mat4 Angel::pers = {};
unsigned int Angel::m_ID = 0;

void Angel::init(unsigned int width, unsigned int height) {

	const float vertices[] = {
	    -1.0f, -1.0f, 0.0f, // bottom left
	    1.0f,  -1.0f, 0.0f, // bottom right
	    1.0f,  1.0f,  0.0f, // top right
	    1.0f,  1.0f,  0.0f, // top right
	    -1.0f, 1.0f,  0.0f, // top left
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
	ResourceManager::LoadShader("res/shaders/pixel/vertex.glsl",
	                            "res/shaders/pixel/fragment.glsl", "pixel");
}

void Angel::enable() {
	glBindVertexArray(m_ID);
	ResourceManager::GetShader("pixel").Bind();
}

void Angel::disable() {
	ResourceManager::GetShader("pixel").Unbind();
	glBindVertexArray(0);
}

unsigned int Angel::getWidth() { return m_width; }
void Angel::setWidth(unsigned int width) { m_width = width; }

unsigned int Angel::getHeight() { return m_height; }
void Angel::setHeight(unsigned int height) { m_height = height; }

oglm::vec2i Angel::map(const float &x, const float &y) {
	int newX = round((x + 1.0f) * m_width / 2);
	int newY = round((y + 1.0f) * m_height / 2);
	return oglm::vec2i(newX, newY);
}
oglm::vec2 Angel::demap(const int &x, const int &y) {
	float newX = x / (float)m_width * 2 - 1.0f;
	float newY = y / (float)m_height * 2 - 1.0f;
	return oglm::vec2(newX, newY);
}

oglm::vec2 Angel::demap(const oglm::vec2i &point) {
	float newX = point.x / (float)m_width * 2 - 1.0f;
	float newY = point.y / (float)m_height * 2 - 1.0f;
	return oglm::vec2(newX, newY);
}

oglm::vec2i Angel::map(const oglm::vec2f &point) {
	int newX = round((point.x + 1.0f) * m_width / 2);
	int newY = round((point.y + 1.0f) * m_height / 2);
	return oglm::vec2i(newX, newY);
}

void Angel::putPixel(float x, float y, int thickness, Color c) {
	enable();
	ResourceManager::GetShader("pixel").SetVec4("inColor",
	                                            glm::vec4(c.r, c.g, c.b, c.a));
	oglm::vec2i point = map(x, y);
	glEnable(GL_SCISSOR_TEST);
	glScissor(point.x, point.y, thickness, thickness);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_SCISSOR_TEST);
	disable();
}

void Angel::drawAxes(Color c, bool octant) {
	for (float i = -1.0f; i <= 1.0f; i += 0.001f) {
		putPixel(0, i, 1, c);
		putPixel(i, 0, 1, c);
	}
}
void Angel::set_perspective(float fov, float aspect, float near, float far) {
	pers = glm::perspective(fov, aspect, near, far);
}
void Angel::set_view(const glm::vec3 &eye, const glm::vec3& towards , const glm::vec3 &up){
	view = glm::lookAt(eye, towards, up);
}
