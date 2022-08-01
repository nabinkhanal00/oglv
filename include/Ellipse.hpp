#pragma once
#include "oglm.hpp"
#include "Angel.hpp"
#include <vector>
class Ellipse {
  private:
	std::vector<oglm::vec2> points;
	std::vector<oglm::vec2> false_points;
	unsigned int thickness;
	unsigned int frameCount;
	float centerX;
	float centerY;
	float majX;
	float majY;

  public:
	Ellipse(float x0, float y0, float a, float b, unsigned int thickness);
	void draw(const oglm::vec4 &color = oglm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	void animate();
	void translate(float x, float y);
	void translate(oglm::vec2 factor);
	void rotate(float radians, float x, float y);
	void rotate(float radians, oglm::vec2 factor);
	void scale(float x, float y);
	void scale(oglm::vec2 factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(float speed);
	void decreaseSpeed(float speed);
};
