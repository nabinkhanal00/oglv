// #include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include "transform.hpp"
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
void Cube::translate(oglm::vec3<int> factor) {
	oglm::mat4<int> trans_mat = oglm::translate(factor);
	for (auto &i : points) {
		oglm::vec4<int> v(i.x, i.y, i.z, 1);
		v = trans_mat * v;
		i = oglm::vec3<int>(v.x, v.y, v.z);
	}
}

void Cube::rotate(float degree, float x, float y, float z) {}
void Cube::rotate(float degree, oglm::vec3<float> factor) {
	// oglm::mat4<float> rot_mat = oglm::rotate(degree, factor);
	oglm::mat4<float> pers_mat = oglm::perspective(0.1f, 1.0f, 0.1f, 100.0f);
	// rot_mat= rot_mat*pers_mat;  
	for (auto &i : points) {
		oglm::vec4<float> v(i.x, i.y, i.z, 1);
		v = pers_mat * v;
		std::cout<<v.w<<std::endl;
		i = oglm::vec3<int>(round(v.x/(float)v.w), round(v.y/(float)v.w), round(v.z/(float)v.w));
	}
}

void Cube::scale(float x, float y, float z) {}
void Cube::scale(oglm::vec3<float> factor) {
	oglm::mat4<float> scale_mat = oglm::scale(factor);
	for (auto &i : points) {
		oglm::vec4<float> v(i.x, i.y, i.z, 1);
		v = scale_mat * v;
		i = oglm::vec3<int>(round(v.x), round(v.y), round(v.z));
	}
}

bool Cube::isCompleted() { return false; }
void Cube::pause() {}
void Cube::reset() {}
void Cube::increaseSpeed(int speed) {}
void Cube::decreaseSpeed(int speed) {}

Cube::~Cube() {}
