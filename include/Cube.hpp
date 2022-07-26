#pragma once

#include "Line.hpp"
#include <vector>
#include <map>

class Cube {
  private:
	std::vector<oglm::vec3> points;
	std::vector<oglm::vec3> drawing_points;
  std::map<std::string,float> depth_buffer;
	std::vector<oglm::vec2i> indices;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Cube(unsigned int length, unsigned int thickness);
	void load();
	void animate();
	void rasterize();
	void translate(float x, float y, float z);
	void translate(oglm::vec3f factor);
	void rotate(float angle, float x, float y, float z);
	void rotate(float angle, oglm::vec3 factor);
	void scale(float x, float y, float z);
	void scale(oglm::vec3 factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(int speed);
	void decreaseSpeed(int speed);
	~Cube();
};
