#pragma once

#include "Shape2D.hpp"
#include <vector>
class Cube : public Shape2D {
  private:
//	std::vector<Line> lines;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Cube(unsigned int thickness);
	void draw();
	void animate();
	void translate(int x, int y);
	void translate(oglm::vec2<int> factor);
	void rotate(int radians, int x, int y);
	void rotate(int radians, oglm::vec2<int> factor);
	void scale(int x, int y);
	void scale(oglm::vec2<int> factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(int speed);
	void decreaseSpeed(int speed);

	~Cube();

};
