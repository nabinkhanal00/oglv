#include "Angel.hpp"
#include "Line.hpp"
#include <algorithm>
#include "ResourceManager.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <stdexcept>

int Angel::m_width = 720;
int Angel::m_height = 720;
int Angel::m_depth = 720;
std::vector<oglm::vec3> Angel::current_buffer;
oglm::mat4 Angel::view;
oglm::mat4 Angel::pers;
oglm::mat4 Angel::model;
std::unordered_map<std::string, float> Angel::depth_buffer;
std::vector<oglm::vec3> Angel::vertexBuffer;
unsigned int Angel::m_ID = 0;
std::vector<oglm::vec3> triangles;
void fillBottomFlatTriangle(const oglm::vec3 &_v1, const oglm::vec3 &_v2,
                            const oglm::vec3 &_v3, const oglm::vec4 &color) {

	oglm::vec3i v1 = Angel::map(_v1);
	oglm::vec3i v2 = Angel::map(_v2);
	oglm::vec3i v3 = Angel::map(_v3);
	float invslope1 = float(v2.x - v1.x) / (v2.y - v1.y);
	float invslope2 = float(v3.x - v1.x) / (v3.y - v1.y);

	float curx1 = v1.x;
	float curx2 = v1.x;

	for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++) {
		oglm::vec2 p0 = Angel::demap(curx1, scanlineY);
		oglm::vec2 p1 = Angel::demap(curx2, scanlineY);
		Line l(p0.x, p0.y, p1.x, p1.y);
		l.draw(color);
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

void fillTopFlatTriangle(const oglm::vec3 &_v1, const oglm::vec3 &_v2,
                         const oglm::vec3 &_v3, const oglm::vec4 &color) {

	oglm::vec3i v1 = Angel::map(_v1);
	oglm::vec3i v2 = Angel::map(_v2);
	oglm::vec3i v3 = Angel::map(_v3);
	float invslope1 = float(v3.x - v1.x) / (v3.y - v1.y);
	float invslope2 = float(v3.x - v2.x) / (v3.y - v2.y);

	float curx1 = v3.x;
	float curx2 = v3.x;

	for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--) {
		oglm::vec2 p0 = Angel::demap(curx1, scanlineY);
		oglm::vec2 p1 = Angel::demap(curx2, scanlineY);
		Line l(p0.x, p0.y, p1.x, p1.y);
		l.draw(color);
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}
void fillTriangle(std::vector<oglm::vec3> &points, const oglm::vec4 &color) {
	std::sort(points.begin(), points.end(),
	          [](oglm::vec3 a, oglm::vec3 b) { return a.y < b.y; });
	oglm::vec3 v1 = points.at(0);
	oglm::vec3 v2 = points.at(1);
	oglm::vec3 v3 = points.at(2);

	/* here we know that v1.y <= v2.y <= v3.y */
	/* check for trivial case of bottom-flat triangle */
	if (fabs(v2.y - v3.y) <= 0.005) {
		fillBottomFlatTriangle(v1, v2, v3, color);
	}
	/* check for trivial case of top-flat triangle */
	else if (fabs(v1.y - v2.y) <= 0.005) {
		fillTopFlatTriangle(v1, v2, v3, color);
	} else {
		/* general case - split the triangle in a topflat and bottom-flat one */
		oglm::vec3 *v4 = new oglm::vec3(
		    (v1.x +
		     ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)),
		    v2.y, v2.z);
		fillBottomFlatTriangle(v1, v2, *v4, color);
		fillTopFlatTriangle(v2, *v4, v3, color);
	}
}
void Angel::draw(const oglm::vec4 &color) {
	for (auto &i : vertexBuffer) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = pers * view * model * v;
		v.x /= v.w;
		v.y /= v.w;
		v.z /= v.w;
		current_buffer.push_back(oglm::vec3(v.x, v.y, v.z));
	}

	int c = 0;
	for (size_t i = 0; i < current_buffer.size() - 1; i = i + 2) {
		float x0 = current_buffer[i].x;
		float y0 = current_buffer[i].y;
		float z0 = (current_buffer[i].z);
		float x1 = current_buffer[i + 1].x;
		float y1 = current_buffer[i + 1].y;
		float z1 = (current_buffer[i + 1].z);
		Line l(x0, y0, z0, x1, y1, z1, 5);
		l.draw3D(color);
		c++;
		if (c % 2 == 0) {
			triangles.push_back(oglm::vec3(x1, y1, z1));
			fillTriangle(triangles, color);
			triangles.clear();

		} else {
			triangles.push_back(oglm::vec3(x0, y0, z0));
			triangles.push_back(oglm::vec3(x1, y1, z1));
		}
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
oglm::vec3 Angel::demap(const oglm::vec3i &point) {
	float newX = point.x / (float)m_width * 2 - 1.0f;
	float newY = point.y / (float)m_height * 2 - 1.0f;
	float newZ = point.z / (float)m_depth * 2 - 1.0f;
	return oglm::vec3(newX, newY, newZ);
}

oglm::vec2i Angel::map(const oglm::vec2f &point) {
	int newX = round((point.x + 1.0f) * m_width / 2);
	int newY = round((point.y + 1.0f) * m_height / 2);
	return oglm::vec2i(newX, newY);
}
oglm::vec3i Angel::map(const oglm::vec3f &point) {
	int newX = round((point.x + 1.0f) * m_width / 2);
	int newY = round((point.y + 1.0f) * m_height / 2);
	int newZ = round((point.y + 1.0f) * m_depth / 2);
	return oglm::vec3i(newX, newY, newZ);
}

void Angel::putPixel(float x, float y, int thickness, const oglm::vec4 &color) {
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

void Angel::drawAxes(oglm::vec4 color, bool octant) {
	for (float i = -1.0f; i <= 1.0f; i += 0.001f) {
		putPixel(0, i, 1, color);
		putPixel(i, 0, 1, color);
	}
}
void Angel::set_perspective(float fov, float aspect, float near, float far) {
	pers = oglm::perspective(fov, aspect, near, far);
}
void Angel::set_view(const oglm::vec3 &eye, const oglm::vec3 &towards,
                     const oglm::vec3 &up) {
	view = oglm::lookAt(eye, towards, up);
}

void Angel::set_model(const oglm::vec3 &tFactor, const oglm::vec3 &sFactor,
                      float rotAng, const oglm::vec3 &rotAxis) {
	oglm::mat4 trans = oglm::translate(tFactor);
	oglm::mat4 scal = oglm::scale(sFactor);
	oglm::mat4 rot = oglm::rotate(rotAng, oglm::normalize(rotAxis));
	// for (int i = 0; i < 4; i++) {
	// 	for (int j = 0; j < 4; j++) {
	// 		std::cout << rot[i][j] << "\t";
	// 	}
	// 	std::cout << std::endl;
	// }
	model = trans * rot * scal;
}
