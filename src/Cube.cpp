// #include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include <iostream>

Cube::Cube(unsigned int length, unsigned int thickness) : thickness(thickness) {
	points.push_back(oglm::vec3<int>(-100.0f, -100.0f, -100.0f));
	points.push_back(oglm::vec3<int>(100.0f, -100.0f, -100.0f));
	points.push_back(oglm::vec3<int>(100.0f, 100.0f, -100.0f));
	points.push_back(oglm::vec3<int>(-100.0f, 100.0f, -100.0f));
	points.push_back(oglm::vec3<int>(-100.0f, -100.0f, 100.0f));
	points.push_back(oglm::vec3<int>(100.0f, -100.0f, 100.0f));
	points.push_back(oglm::vec3<int>(100.0f, 100.0f, 100.0f));
	points.push_back(oglm::vec3<int>(-100.0f, 100.0f, 100.0f));

	indices.push_back(oglm::vec2<int>(0, 1));
	indices.push_back(oglm::vec2<int>(1, 2));
	indices.push_back(oglm::vec2<int>(2, 3));
	indices.push_back(oglm::vec2<int>(0, 3));

	indices.push_back(oglm::vec2<int>(0, 4));
	indices.push_back(oglm::vec2<int>(1, 5));
	indices.push_back(oglm::vec2<int>(2, 6));
	indices.push_back(oglm::vec2<int>(3, 7));

	indices.push_back(oglm::vec2<int>(4, 5));
	indices.push_back(oglm::vec2<int>(5, 6));
	indices.push_back(oglm::vec2<int>(6, 7));
	indices.push_back(oglm::vec2<int>(7, 4));
}

void Cube::animate() {}

void Cube::draw() {
	for (auto &i : indices) {
		Line l(points[i.x].x, points[i.x].y, points[i.y].x, points[i.y].y);
		l.draw();
	}
}
void Cube::translate(int x, int y, int z) {}
void Cube::translate(oglm::vec3<int> factor) {
	oglm::mat4<int> trans_mat = oglm::translate(factor);
	for (auto &i : points) {
		oglm::vec4<int> v(i.x, i.y, i.z, 1);
		v= trans_mat * v;
		i = oglm::vec3<int>(v.x, v.y, v.z);
	}
}
void Cube::rotate(int radians, int x, int y, int z) {}
void Cube::rotate(int radians, oglm::vec3<int> factor) {
	oglm::mat4<int> rot_mat = oglm::rotate(radians, factor);
	for (auto &i : points) {
		oglm::vec4<int> v(i.x, i.y, i.z, 1);
		v= rot_mat * v;
		i = oglm::vec3<int>(v.x, v.y, v.z);
	}
}
void Cube::scale(int x, int y, int z) {}
void Cube::scale(oglm::vec3<int> factor) {
	oglm::mat4<int> scale_mat = oglm::scale(factor);
	for (auto &i : points) {
		oglm::vec4<int> v(i.x, i.y, i.z, 1);
		v= scale_mat * v;
		i = oglm::vec3<int>(v.x, v.y, v.z);
	}
}
bool Cube::isCompleted() { return false; }
void Cube::pause() {}
void Cube::reset() {}
void Cube::increaseSpeed(int speed) {}
void Cube::decreaseSpeed(int speed) {}

Cube::~Cube() {}
