#include "Line.hpp"
#include "Angel.hpp"
#include <iostream>

Line::Line(int x0, int y0, int xl, int yl, unsigned int t)
    : thickness(t), frameCount(60) {
	int delx = std::abs(xl - x0);
	int dely = std::abs(yl - y0);
	int a = 0, b = 0;
	int p = 0;
	a = ((xl - x0) > 0) ? thickness : -thickness;
	b = ((yl - y0) > 0) ? thickness : -thickness;
	int tempx = x0, tempy = y0;
	if (delx > dely) {
		p = 2 * dely - delx;
		for (int i = 0; i <= delx; i += thickness) {
			points.push_back(oglm::vec2<int>(x0, y0));
			false_points.push_back(oglm::vec2<int>(tempx, tempy));
			x0 += a;
			tempx += a;
			if (p <= 0) {
				p += 2 * dely;
				tempy = y0 + b;
			} else {
				p += 2 * dely - 2 * delx;
				tempy = y0;
				y0 += b;
			}
		}
	} else {
		p = 2 * delx - dely;
		for (int i = 0; i <= dely; i += thickness) {
			points.push_back(oglm::vec2<int>(x0, y0));
			false_points.push_back(oglm::vec2<int>(tempx, tempy));
			y0 += b;
			tempy += b;
			if (p <= 0) {
				tempx = x0 + a;
				p += 2 * delx;
			} else {
				p += 2 * delx - 2 * dely;
				tempx = x0;
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
	static int stuck = 0;

	int cur;
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x, points[cur].y, thickness);
	}
	Angel::putPixel(points[points.size() - 1].x, points[points.size() - 1].y,
	                thickness);
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(points[i].x, points[i].y, thickness,
				                Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(false_points[i].x, false_points[i].y, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x, points[cur - 1].y, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	if (i < points.size()) {
		if (count >= frameCount) {
			stuck = 0;
			i++;
			count = 0;
		} else {
			count++;
			stuck++;
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
