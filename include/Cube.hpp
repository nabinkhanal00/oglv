#pragma once

#include "Shape3D.hpp"
#include "Line.hpp"
#include <vector>

class Cube {
  private:
	std::vector<oglm::vec3<int>> points;
	std::vector<oglm::vec2<int>> indices;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Cube(unsigned int length, unsigned int thickness);
	void draw();
	void animate();
	void translate(int x, int y, int z);
	void translate(oglm::vec3<int> factor);
	void rotate(float angle, float x, float y, float z);
	void rotate(float angle, oglm::vec3<float> factor);
	void scale(float x, float y, float z);
	void scale(oglm::vec3<float> factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(int speed);
	void decreaseSpeed(int speed);
	~Cube();
};
