#pragma once

#include "Shape3D.hpp"
#include "Line.hpp"
#include <vector>
class Cube {
  private:
	std::vector<oglm::vec3<int>> points;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Cube(unsigned int length, unsigned int thickness);
	void draw();
	void animate();
	void translate(int x, int y, int z);
	void translate(oglm::vec3<int> factor);
	void rotate(int radians, int x, int y, int z);
	void rotate(int radians, oglm::vec3<int> factor);
	void scale(int x, int y, int z);
	void scale(oglm::vec3<int> factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(int speed);
	void decreaseSpeed(int speed);
	~Cube();

};
