#pragma once

#include "Color.hpp"
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

	static void putPixel(int x, int y, int width = 1,
	                     Color c = {1.0f, 1.0f, 1.0f, 1.0f});

	static void drawAxes(Color c = {1.0f, 1.0f, 1.0f, 1.0f});
	static void enable();
	static void disable();

  private:
	static unsigned int m_ID;
	static Color m_color;
	static int m_width;
	static int m_height;
};
