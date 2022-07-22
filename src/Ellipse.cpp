#include "Ellipse.hpp"
#include "Color.hpp"
#include "Line.hpp"
#include <iostream>
Ellipse::Ellipse(float x0, float y0, float rX, float rY, unsigned int t)
    : thickness(t), frameCount(60) {
	centerX = x0;
	centerY = y0;
	majX = rX;
	majY = rY;
	// int rx = rX * Angel::getWidth() / 2;
	// int ry = rX * Angel::getHeight() / 2;
	float rx = rX;
	float ry = rY;
	float dx, dy, d1, d2;
	float x, y;
	x = 0;
	y = ry;

	// Initial decision parameter of region 1
	d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;
	float falseX{x}, falseY{y};

	// For region 1
	while (dx <= dy) {
		points.push_back(Angel::demap(x, y));
		false_points.push_back(Angel::demap(falseX, falseY));

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

		points.push_back(Angel::demap(x, y));
		false_points.push_back(Angel::demap(falseX, falseY));
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

void Ellipse::draw() {

	for (auto &i : points) {
        // std::cout<<i.x<<" "<<i.y<<" "<<std::endl;
		Angel::putPixel(i.x + centerX, i.y + centerY, thickness);
        // std::cout<<-i.x<<" "<<i.y<<" "<<std::endl;
		Angel::putPixel(-i.x + centerX, i.y + centerY, thickness);
        // std::cout<<i.x<<" "<<-i.y<<" "<<std::endl;
		Angel::putPixel(i.x + centerX, -i.y + centerY, thickness);
        // std::cout<<-i.x<<" "<<-i.y<<" "<<std::endl;
		Angel::putPixel(-i.x + centerX, -i.y + centerY, thickness);
	}
}

void Ellipse::animate() {
	static int count = 0;
	static int i = 0;
	static int stuck = 0;
	int cur;
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x + centerX, points[cur].y + centerY,
		                thickness);
	}
	for (int cur = 0; cur < i; cur++) {
		Angel::putPixel(-points[cur].x + centerX, points[cur].y + centerY,
		                thickness);
	}

	for (int cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x + centerX, -points[cur].y + centerY,
		                thickness);
	}
	for (int cur = 0; cur < i; cur++) {
		Angel::putPixel(-points[cur].x + centerX, -points[cur].y + centerY,
		                thickness);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10 + 4) % 2 == 0) {
				Angel::putPixel(points[i].x, points[i].y, thickness,
				                Color(1.0f, 0.0f, 1.0f, 1.0f));
				Angel::putPixel(-points[i].x, points[i].y, thickness,
				                Color(1.0f, 0.0f, 1.0f, 1.0f));
				Angel::putPixel(points[i].x, -points[i].y, thickness,
				                Color(1.0f, 0.0f, 1.0f, 1.0f));
				Angel::putPixel(-points[i].x, -points[i].y, thickness,
				                Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(false_points[i].x, false_points[i].y, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
				Angel::putPixel(-false_points[i].x, false_points[i].y,
				                thickness, Color(0.0f, 0.0f, 1.0f, 1.0f));
				Angel::putPixel(false_points[i].x, -false_points[i].y,
				                thickness, Color(0.0f, 0.0f, 1.0f, 1.0f));
				Angel::putPixel(-false_points[i].x, -false_points[i].y,
				                thickness, Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x, points[cur - 1].y, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
				Angel::putPixel(-points[cur - 1].x, points[cur - 1].y,
				                thickness, Color(1.0f, 0.0f, 0.0f, 1.0f));
				Angel::putPixel(points[cur - 1].x, -points[cur - 1].y,
				                thickness, Color(1.0f, 0.0f, 0.0f, 1.0f));
				Angel::putPixel(-points[cur - 1].x, -points[cur - 1].y,
				                thickness, Color(1.0f, 0.0f, 0.0f, 1.0f));
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
