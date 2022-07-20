#include "Line.hpp"
#include "Angel.hpp"
#include "Shape2D.hpp"
#include <iostream>

Line::Line(int x0, int y0, int xl, int yl, unsigned int t)
    : thickness(t), frameCount(20) {
	int delx = std::abs(xl - x0);
	int dely = std::abs(yl - y0);
	int a = 0, b = 0;
	int p = 0;
	a = ((xl - x0) > 0) ? thickness : -thickness;
	b = ((yl - y0) > 0) ? thickness : -thickness;
	if (delx > dely) {
		p = 2 * dely - delx;
		for (int i = 0; i <= delx; i += thickness) {
			points.push_back(oglm::vec2<int>(x0, y0));
			x0 += a;
			if (p <= 0)
				p += 2 * dely;
			else {
				p += 2 * dely - 2 * delx;
				y0 += b;
			}
		}
	} else {
		p = 2 * delx - dely;
		for (int i = 0; i <= dely; i += thickness) {
			points.push_back(oglm::vec2<int>(x0, y0));
			y0 += b;
			if (p <= 0)
				p += 2 * delx;
			else {
				p += 2 * delx - 2 * dely;
				x0 += a;
			}
		}
	}
}

void Line::draw() {
	Color(1.0f, 1.0f, 1.0f, 1.0f);

	for (auto &i : points) {
		Angel::putPixel(i.x, i.y, thickness);
	}
}
void Line::animate() {
	static int count = 0;
	static int i = 0;
	for (int cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x, points[cur].y, thickness);
	}
	if (i < points.size()) {
		if (count >= frameCount) {
			i++;
			count = 0;
		} else {
			count++;
		}
	}
}
void Line::translate(int x, int y) {}
void Line::translate(oglm::vec2<int> factor) {}
void Line::rotate(int radians, int x, int y) {}
void Line::rotate(int radians, oglm::vec2<int> factor) {}
void Line::scale(int x, int y) {}
void Line::scale(oglm::vec2<int> factor) {}
bool Line::isCompleted() { return false; }
void Line::pause() {}
void Line::reset() {}
void Line::increaseSpeed(int speed) {}
void Line::decreaseSpeed(int speed) {}
