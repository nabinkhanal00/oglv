#pragma once

#include "glad.h"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer {
  public:
	void Clear() const;
	void Draw(const VertexArray &va, const IndexBuffer &ib,
	          const Shader &shader, const unsigned int type = GL_TRIANGLES) const;
};
