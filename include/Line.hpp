#pragma once

#include "Shape2D.hpp"
#include "Angel.hpp"
#include <vector>
class Line : public Shape2D {
  private:
	std::vector<oglm::vec2<int>> points;
	Angel angel;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Line(int x1, int y1, int x2, int y2, unsigned int thickness,
	     unsigned int windowWidth, unsigned int windowHeight);
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
};
