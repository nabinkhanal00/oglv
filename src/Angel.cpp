#include "Angel.hpp"
#include "Line.hpp"
#include "ResourceManager.hpp"
#include "VertexBuffer.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

int Angel::m_width = 1280;
int Angel::m_height = 720;

oglm::mat4<float> Angel::view;
oglm::mat4<float> Angel::pers;
std::map<std::string, float> Angel::depth_buffer;
std::vector<oglm::vec3> Angel::vertexBuffer;
unsigned int Angel::m_ID = 0;

void Angel::draw() {
	oglm::mat4<float> scal = oglm::scale(oglm::vec3(1.0f, 1.0f, 1.0f));
	oglm::mat4<float> trans = oglm::translate(oglm::vec3(0.0f, 0.0f, 0.0f));
	oglm::mat4<float> rot = oglm::rotate(0.0f, oglm::vec3(0.0f, 0.0f, 0.0f));

	set_perspective((float)M_PI_2, getWidth() / (float)getHeight(), 0.1,
	                100.0f);
	set_view(oglm::vec3(0.0f, 0.0f, 4.0f), oglm::vec3(0.0f, 0.0f, 0.0f),
	         oglm::vec3(0.0f, 1.0f, 0.0f));
	for (auto &i : vertexBuffer) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = pers * view * trans * rot * scal * v;
		v /= v.w;
		i = oglm::vec3(v.x, v.y, v.z);
	}
	for (size_t i = 0; i < vertexBuffer.size() - 2; i = i + 2) {
		float x0 = vertexBuffer[i].x;
		float y0 = vertexBuffer[i].y;
		float z0 = vertexBuffer[i].z;
		float x1 = vertexBuffer[i + 1].x;
		float y1 = vertexBuffer[i + 1].y;
		float z1 = vertexBuffer[i + 1].z;

		oglm::vec2i x0y0 = Angel::map(x0, y0);
		oglm::vec2i x1y1 = Angel::map(x1, y1);
		std::string key = std::to_string(x0y0.x) + ',' + std::to_string(x0y0.y);
		std::string key2 =
		    std::to_string(x1y1.x) + ',' + std::to_string(x1y1.y);
		Line l(x0, y0, x1, y1);
		l.draw();
		// if (z0 >= depth_buffer[key] && z1 >= depth_buffer[key2]) {
		// }
	}
}

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
void Angel::init_depth_buffer() {
	// iniatilizing depth buffer
	depth_buffer.clear();
	for (size_t i = 0; i <= Angel::getWidth(); i++) {
		for (size_t j = 0; j <= Angel::getHeight(); j++) {
			std::string key = std::to_string(i) + ',' + std::to_string(j);
			depth_buffer[key] = 0.0f;
		}
	}
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
	pers = oglm::perspective(fov, aspect, near, far);
}
void Angel::set_view(const oglm::vec3 &eye, const oglm::vec3 &towards,
                     const oglm::vec3 &up) {
	view = oglm::lookAt(eye, towards, up);
}
