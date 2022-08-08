#include "Ellipse.hpp"
#include "Color.hpp"
#include <iostream>
Ellipse::Ellipse(int x0, int y0, int rx, int ry, unsigned int t)
    : thickness(t), frameCount(60) {
	majX = rx;
	majY = ry;
	centerX = x0;
	centerY = y0;

	int dx, dy, d1, d2;
	int x, y;
	x = 0;
	y = ry;

	// Initial decision parameter of region 1
	d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;
	int falseX{x}, falseY{y};

	// For region 1
	while (dx <= dy) {
		points.push_back(oglm::vec2i(x, y));
		false_points.push_back(oglm::vec2i(x, y));

		// Checking and updating value of
		// decision parameter based on algorithm
		if (d1 < 0) {
			falseY = y - thickness;
			x += thickness;
			falseX = x;

			dx = 2 * ry * ry * x;
			d1 = d1 + dx + (ry * ry);
		} else {
			x += thickness;
			falseX = x;
			falseY = y;
			y -= thickness;
			dx = 2 * ry * ry * x;
			dy = 2 * rx * rx * y;
			d1 = d1 + dx - dy + (ry * ry);
		}
	}

	// Decision parameter of region 2
	d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
	     ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

	// Plotting points of region 2
	while (y >= 0) {

		points.push_back(oglm::vec2i(x, y));
		false_points.push_back(oglm::vec2i(falseX, falseY));
		// Checking and updating parameter
		// value based on algorithm
		if (d2 > 0) {
			// y--;
			falseX = x + thickness;
			y -= thickness;
			falseY = y;
			// dy = dy - (2 * rx * rx);
			dy = 2 * rx * rx * y;
			d2 = d2 + (rx * rx) - dy;
		} else {
			// y--;
			y -= thickness;
			falseY = y;
			// x++;
			falseX = x;
			x += thickness;
			// dx = dx + (2 * ry * ry);
			dx = 2 * ry * ry * x;
			// dy = dy - (2 * rx * rx);
			dy = 2 * rx * rx * y;
			d2 = d2 + dx - dy + (rx * rx);
		}
	}
}

void Ellipse::draw(const oglm::vec4 &color) {

	for (auto &i : points) {
		Angel::putPixel(i.x + centerX, i.y + centerY, thickness, color);
		Angel::putPixel(-i.x + centerX, i.y + centerY, thickness, color);
		Angel::putPixel(i.x + centerX, -i.y + centerY, thickness, color);
		Angel::putPixel(-i.x + centerX, -i.y + centerY, thickness, color);
	}
}

void Ellipse::animate() {
	static int count = 0;
	static int i = 0;
	static int stuck = 0;
	int cur;

	static const oglm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
	static const oglm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
	static const oglm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
	static const oglm::vec4 green(0.0f, 1.0f, 0.0f, 1.0f);
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(false_points[cur].x + centerX,
		                false_points[cur].y + centerY, thickness, blue);
		Angel::putPixel(points[cur].x + centerX, points[cur].y + centerY,
		                thickness, white);
	}
	for (int cur = 0; cur < i; cur++) {
		Angel::putPixel(-false_points[cur].x + centerX,
		                false_points[cur].y + centerY, thickness, blue);
		Angel::putPixel(-points[cur].x + centerX, points[cur].y + centerY,
		                thickness, white);
	}

	for (int cur = 0; cur < i; cur++) {
		Angel::putPixel(false_points[cur].x + centerX,
		                -false_points[cur].y + centerY, thickness, blue);
		Angel::putPixel(points[cur].x + centerX, -points[cur].y + centerY,
		                thickness, white);
	}
	for (int cur = 0; cur < i; cur++) {
		Angel::putPixel(-false_points[cur].x + centerX,
		                -false_points[cur].y + centerY, thickness, blue);
		Angel::putPixel(-points[cur].x + centerX, -points[cur].y + centerY,
		                thickness, white);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10 + 4) % 2 == 0) {
				Angel::putPixel(points[i].x + centerX, points[i].y + centerY,
				                thickness, red);
				Angel::putPixel(-points[i].x + centerX, points[i].y + centerY,
				                thickness, red);
				Angel::putPixel(points[i].x + centerX, -points[i].y + centerY,
				                thickness, red);
				Angel::putPixel(-points[i].x + centerX, -points[i].y + centerY,
				                thickness, red);
			} else {
				Angel::putPixel(false_points[i].x + centerX,
				                false_points[i].y + centerY, thickness, blue);
				Angel::putPixel(-false_points[i].x + centerX,
				                false_points[i].y + centerY, thickness, blue);
				Angel::putPixel(false_points[i].x + centerX,
				                -false_points[i].y + centerY, thickness, blue);
				Angel::putPixel(-false_points[i].x + centerX,
				                -false_points[i].y + centerY, thickness, blue);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x + centerX,
				                points[cur - 1].y + centerY, thickness, red);
				Angel::putPixel(-points[cur - 1].x + centerX,
				                points[cur - 1].y + centerY, thickness, red);
				Angel::putPixel(points[cur - 1].x + centerX,
				                -points[cur - 1].y + centerY, thickness, red);
				Angel::putPixel(-points[cur - 1].x + centerX,
				                -points[cur - 1].y + centerY, thickness, red);
			}
		}
	}
	if (i < points.size()) {
		if (count >= frameCount) {
			i++;
			count = 0;
			stuck = 0;
		} else {
			count++;
			stuck++;
		}
	}
};
void Ellipse::translate(float x, float y){};
void Ellipse::translate(oglm::vec2 factor){};
void Ellipse::rotate(float radians, float x, float y){};
void Ellipse::rotate(float radians, oglm::vec2 factor){};
void Ellipse::scale(float x, float y){};
void Ellipse::scale(oglm::vec2 factor){};
bool Ellipse::isCompleted() { return true; };
void Ellipse::pause(){};
void Ellipse::reset(){};
void Ellipse::increaseSpeed(float speed){};
void Ellipse::decreaseSpeed(float speed){};
