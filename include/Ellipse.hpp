#pragma once
#include "oglm.hpp"
#include "Angel.hpp"
#include <vector>
class Ellipse {
  private:
	std::vector<oglm::vec2i> points;
	std::vector<oglm::vec2i> false_points;
        unsigned int thickness;
        int centerX;
        int centerY;
        int majX;
        int majY;

  public:
	Ellipse(int x0, int y0, int a, int b, unsigned int thickness);
        void draw(const oglm::vec4 &color = oglm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        static unsigned int frameCount;
        static int count;
        static int i;
        static int stuck;
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
