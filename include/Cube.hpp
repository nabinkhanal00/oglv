#pragma once

#include "Line.hpp"
#include <vector>
#include <map>

class Cube {
  private:
	std::vector<oglm::vec3> points;
	std::vector<oglm::vec3> vertexBuffer;
	std::vector<oglm::vec4> currentBuffer;
	std::map<std::string, float> depth_buffer;
	std::vector<oglm::vec2i> indices;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Cube(unsigned int length, unsigned int thickness);
	// void draw(const oglm::vec4 &color = {1.0f, 1.0f, 1.0f, 1.0f});
	void draw(bool lineFill = true, bool isLightedObject = false,
	          const oglm::vec4 &color = {1.0f, 1.0f, 1.0f, 1.0f},
	          const oglm::vec3 &lightPos = {1.0f, 0.0f, 0.0f},
	          const oglm::vec4 &lightcolor = {1.0f, 1.0f, 1.0f, 1.0f});

	void set_model(const oglm::vec3 &tFactor, const oglm::vec3 &sFactor,
	               float rotAng, const oglm::vec3 &rotAxis);
	void rasterize();
	void load(bool doRasterize = false);
	static bool clipping;
	oglm::mat4 model;
	~Cube(){};
};
