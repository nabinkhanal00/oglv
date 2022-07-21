// #include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include <iostream>

Cube::Cube(unsigned int length, unsigned int thickness) : thickness(thickness) {
	points.push_back(oglm::vec3i(-100.0f, -100.0f, -100.0f));
	points.push_back(oglm::vec3i(100.0f, -100.0f, -100.0f));
	points.push_back(oglm::vec3i(100.0f, 100.0f, -100.0f));
	points.push_back(oglm::vec3i(-100.0f, 100.0f, -100.0f));
	points.push_back(oglm::vec3i(-100.0f, -100.0f, 100.0f));
	points.push_back(oglm::vec3i(100.0f, -100.0f, 100.0f));
	points.push_back(oglm::vec3i(100.0f, 100.0f, 100.0f));
	points.push_back(oglm::vec3i(-100.0f, 100.0f, 100.0f));

	indices.push_back(oglm::vec2i(0, 1));
	indices.push_back(oglm::vec2i(1, 2));
	indices.push_back(oglm::vec2i(2, 3));
	indices.push_back(oglm::vec2i(0, 3));

	indices.push_back(oglm::vec2i(0, 4));
	indices.push_back(oglm::vec2i(1, 5));
	indices.push_back(oglm::vec2i(2, 6));
	indices.push_back(oglm::vec2i(3, 7));

	indices.push_back(oglm::vec2i(4, 5));
	indices.push_back(oglm::vec2i(5, 6));
	indices.push_back(oglm::vec2i(6, 7));
	indices.push_back(oglm::vec2i(7, 4));
}

void Cube::animate() {}

void Cube::draw() {
	static int num = 0;
	for (auto &i : indices) {
		Line l(points[i.x].x, points[i.x].y, points[i.y].x, points[i.y].y);
		l.draw();
		if (num == 0) {
			std::cout << points[i.x] << "\t" << points[i.y] << std::endl;
		}
	}
	if (num == 0)
		num = 1;
}

void Cube::translate(int x, int y, int z) {}
void Cube::translate(oglm::vec3i factor) {
	oglm::mat4<int> trans_mat = oglm::translate(factor);
	for (auto &i : points) {
		oglm::vec4i v(i.x, i.y, i.z, 1);
		v = trans_mat * v;
		i = oglm::vec3i(v.x, v.y, v.z);
	}
}

void Cube::rotate(float degree, float x, float y, float z) {}
void Cube::rotate(float degree, oglm::vec3 factor) {
	oglm::mat4<float> rot_mat = oglm::rotate(degree, factor);
	rot_mat = oglm::perspective((float)M_PI_2, 1.0f, 0.1f, 100.0f) * rot_mat;
	for (auto &i : points) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = rot_mat * v;
		i = oglm::vec3i(round(v.x / (float)v.w), round(v.y / (float)v.w),
		                round(v.z / (float)v.w));
	}
}

void Cube::scale(float x, float y, float z) {}
void Cube::scale(oglm::vec3 factor) {
	oglm::mat4<float> scale_mat = oglm::scale(factor);
	for (auto &i : points) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = scale_mat * v;
		i = oglm::vec3i(round(v.x), round(v.y), round(v.z));
	}
}

bool Cube::isCompleted() { return false; }
void Cube::pause() {}
void Cube::reset() {}
void Cube::increaseSpeed(int speed) {}
void Cube::decreaseSpeed(int speed) {}

Cube::~Cube() {}
