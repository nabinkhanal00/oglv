#pragma once

#include "Color.hpp"
#include "oglm.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBufferElement.hpp"

class Angel {
  public:
	Angel();

	static void init(unsigned int width, unsigned int height);

	static void putPixel(float x, float y, int width = 1,
	                     Color c = {1.0f, 1.0f, 1.0f, 1.0f});

	static void drawAxes(Color c = {1.0f, 1.0f, 1.0f, 1.0f},
	                     bool octant = false);
	static void enable();
	static void disable();
	static void setHeight(unsigned int height);
	static void setWidth(unsigned int width);
	static unsigned int getWidth();
	static unsigned int getHeight();
	static oglm::vec2i map(const float &x, const float &y);
	static oglm::vec2f demap(const int &x, const int &y);
	static oglm::vec2i map(const oglm::vec2 &point);
	static oglm::vec2f demap(const oglm::vec2i &point);

  private:
	static unsigned int m_ID;
	static Color m_color;
	static int m_width;
	static int m_height;
};
