#pragma once

#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBufferElement.hpp"

class Angel {
  public:
	struct color {
		float r;
		float g;
		float b;
		float a;
	};

	Angel(unsigned int width, unsigned int height);

	void putPixel(int x, int y, int width = 1,
	              color c = {1.0f, 1.0f, 1.0f, 1.0f}) const;

	void drawAxes(color c = {1.0f, 1.0f, 1.0f, 1.0f});
	void enable();
	void disable();

  private:
	VertexBuffer m_vb;
	VertexArray m_va;
	Shader m_shader;
	color m_color;
	int m_width;
	int m_height;
};
