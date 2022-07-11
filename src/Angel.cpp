#include "Angel.hpp"

const float vertices[] = {
    -1.0f, -1.0f, 0.0f, // bottom left
    1.0f,  -1.0f, 0.0f, // bottom right
    1.0f,  1.0f,  0.0f, // top right
    1.0f,  1.0f,  0.0f, // top right
    -1.0f, 1.0f,  0.0f, // top left
	-1.0f, -1.0f, 0.0f, // bottom left
};
Angel::Angel(unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_vb(vertices, 6 * 3 * sizeof(float))
       {
	VertexBufferLayout layout;
	layout.AddFloat(3);
	m_va.AddBuffer(m_vb, layout);
	m_shader = Shader("res/shaders/pixel/vertex.glsl",
	                  "res/shaders/pixel/fragment.glsl");
}

void Angel::enable() {
	m_shader.Use();
	m_va.Bind();
}

void Angel::disable() { m_va.Unbind(); }

void Angel::putPixel(int x, int y, int thickness, color c) const {
	m_shader.SetVec4("inColor", glm::vec4(c.r, c.g, c.b, c.a));
	x += m_width / 2;
	y += m_height / 2;
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, thickness, thickness);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_SCISSOR_TEST);
}
