#pragma once

#include "Color.hpp"
#include "oglm.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBufferElement.hpp"
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/mat4x4.hpp>
#include <unordered_map>

class Angel {
  public:
	Angel();

	static void init(unsigned int width, unsigned int height);
	static void init_depth_buffer();
	static std::vector<oglm::vec3> current_buffer;

	static void putPixel(float x, float y, int width = 4,
	                     Color c = {1.0f, 1.0f, 1.0f, 1.0f});

	static void drawAxes(Color c = {1.0f, 1.0f, 1.0f, 1.0f},
	                     bool octant = false);
	static void enable();
	static void set_perspective(float fov, float aspect, float near, float far);
	static void set_view(const oglm::vec3 &eye, const oglm::vec3 &towards,
	                     const oglm::vec3 &up);
	static void set_model(const oglm::vec3 &tFactor, const oglm::vec3 &sFactor,
	                      float rotAng, const oglm::vec3 &rotAxis);
	static void disable();
	static void setHeight(unsigned int height);
	static void setWidth(unsigned int width);
	static unsigned int getWidth();
	static unsigned int getHeight();
	static oglm::vec2i map(const float &x, const float &y);
	static oglm::vec2f demap(const int &x, const int &y);
	static oglm::vec2i map(const oglm::vec2 &point);
	static oglm::vec2f demap(const oglm::vec2i &point);
	static oglm::mat4<float> pers;
	static oglm::mat4<float> view;
	static oglm::mat4<float> model;
	static std::unordered_map<std::string, float> depth_buffer;
	static std::vector<oglm::vec3> vertexBuffer;
	static void draw();

  private:
	static unsigned int m_ID;
	static Color m_color;
	static int m_width;
	static int m_height;
};
